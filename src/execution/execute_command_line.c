/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:02:32 by psalame           #+#    #+#             */
/*   Updated: 2024/01/19 22:26:12 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "minishell.h"
#include <errno.h>
#include <unistd.h>

// find_cmd
// fork() if not built-in
// child1->execve cmd
// parent1->if succ or error defined
//         fork()
//          child2->waitpid(child)
//                  execute_command_line(group_data->on_success || group_data->on_error)
//

int count_pipe(t_command_group *command_line)
{
	int i;

	i = 0;
	while(command_line)
	{
		command_line = command_line->pipe_next;
		i++;
	}
	return (i);
}

static int	execute_command(t_command *command, t_command_group *group_data, int fd[2])
{
	int		child_pid;
	int		baby_pid;
	int		child_pid_res;

	baby_pid = -1;
	child_pid = fork();
	if (child_pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		command->executable = find_cmd(command->executable, convert_env_data_to_strs(group_data->env->env));
		execve(command->executable, command->arguments, convert_env_data_to_strs(group_data->env->env)); // todo add premake of char **env in t_env_data for free at end
		exit(errno);
	}
	else if (group_data->on_success || group_data->on_error)
	{
		waitpid(child_pid, &child_pid_res, 0);
		baby_pid = fork();
		if (baby_pid == 0)
		{
			// child_pid_res = wait4(child_pid, NULL, WNOHANG, NULL);
			child_pid_res = WEXITSTATUS(child_pid_res);
			if (child_pid_res != 0)
			{
				if (group_data->on_error != NULL)
					execute_command_line(group_data->on_error);
				exit(errno); // must be res of execute_command_line
			}
			else
			{
				if (group_data->on_success != NULL)
					execute_command_line(group_data->on_success);
				exit(EXIT_SUCCESS); // must be res of execute_command_line
			}
		}
		else
			return (baby_pid);
	}
	return (child_pid);
}


static void	close_pipe(int fd[2])
{
	if (fd[0] > 0)
		close(fd[0]);
	if (fd[1] > 0)
		close(fd[1]);
}

static void	wait_multiple_pid(int *pid, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
}

static void	manage_pipe(int fd[2][2], int i, int size)
{
	if (i == size - 1)
		dup2(fd[(i + 1) % 2][0], STDIN_FILENO);
	else if (i == 0)
		dup2(fd[0][1], STDOUT_FILENO);
	else
	{
		dup2(fd[(i + 1) % 2][0], STDIN_FILENO);
		dup2(fd[i % 2][1], STDOUT_FILENO);
	}
	close_pipe(fd[0]);
	if (i > 0)
		close_pipe(fd[1]);
}

void pipe_cmd(t_command_group *command_line, int *pid, int fd[2][2], int index, int pipe_count)
{
	int child;

	if (pipe(fd[index % 2]) == -1)
		exit(errno);
	if (command_line->command)
	{
		pid[index] = fork();
		if (pid[index] == 0)
		{
			manage_pipe(fd, index, pipe_count);
			child = execute_command(command_line->command, command_line, fd[index % 2]);
			waitpid(child, NULL, 0);
			exit(1);
		}
	}
	if (index != 0)
		close_pipe(fd[(index + 1) % 2]);
	if (command_line->pipe_next)
		pipe_cmd(command_line->pipe_next, pid, fd, index + 1, pipe_count);
	close_pipe(fd[index % 2]);
	wait_multiple_pid(pid, pipe_count);
}

int	execute_command_line(t_command_group *command_line)
{
	//int	child;
	int	fd[2][2];
	int *pid;
	int pid_count;

	pid_count = count_pipe(command_line);
	pid = malloc(pid_count * sizeof(int));
	pipe_cmd(command_line, pid, fd, 0, pid_count);
	return (0);
}
