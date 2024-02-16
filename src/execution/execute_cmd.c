/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 21:00:20 by babonnet          #+#    #+#             */
/*   Updated: 2024/02/15 21:25:52 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "command_Int.h"
#include <errno.h>
#include <unistd.h>

static int	get_pid_res(int pid)
{
	int	pid_res;

	waitpid(pid, &pid_res, 0);
	if (!WIFEXITED(pid_res))
	{
		if ((WCOREDUMP(pid_res)))
		{
			ft_dprintf(2, "Quit (core dumped)\n");
			return (131);
		}
		else
		{
			ft_dprintf(2, "\n");
			return (130);
		}
	}
	return (WEXITSTATUS(pid_res));
}

int	execute_command(t_command *command, t_command_group *group_data, int fd[2])
{
	int		child_pid;
	int		child_pid_res;

	convert_variable_arguments(command);
	command->executable = command->arguments[0];
	if (is_command_builtin(command->executable))
		child_pid = execute_builtin_command(command);
	else
	{
		command->executable = find_cmd(command->executable, *(command->env));
		child_pid = fork();
		if (child_pid == 0)
		{
			if (fd != NULL)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
			}
			manage_infile(command->infiles, STDIN_FILENO);
			manage_outfile(command->outfiles, STDOUT_FILENO);
			if (command->executable == NULL)
			{
				ft_dprintf(2, "%s: command not found\n",command->arguments[0]);
				find_close_cmd(command->arguments[0]); // todo fix leak
			}
			else
			{
				execve(command->executable, command->arguments, *(command->env));
				ft_dprintf(2, "%s: %s: %s\n", command->exec_data.shell_data->exec_name, command->arguments[0], strerror(errno));
			}
			free(command->executable);
			free(command->exec_data.pid);
			free_shell_data(command->exec_data.shell_data, false);
			free_command_line(command->exec_data.base_command_line, false);
			free_command_line(NULL, true);
			exit(127);
		}
		free(command->executable);
	}
	if (child_pid < 0)
		child_pid_res = -child_pid - 1;
	else
		child_pid_res = get_pid_res(child_pid);
	if ((child_pid_res != 0 && group_data->on_error != NULL) || (child_pid_res == 0 && group_data->on_success != NULL))
	{
		int	forked = command->exec_data.forked;
		command->exec_data.forked = false;
		if (child_pid_res != 0 && group_data->on_error != NULL)
			child_pid_res = execute_command_line(group_data->on_error, command->exec_data);
		else if (child_pid_res == 0 && group_data->on_success != NULL)
			child_pid_res = execute_command_line(group_data->on_success, command->exec_data);
		command->exec_data.forked = forked;
	}
	if (command->exec_data.forked)
	{
		free(command->exec_data.pid);
		free_shell_data(command->exec_data.shell_data, false);
		free_command_line(command->exec_data.base_command_line, false);
		free_command_line(NULL, true);
	}
	return (child_pid_res);
}
