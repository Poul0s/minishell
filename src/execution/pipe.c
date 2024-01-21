/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:19:10 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/21 22:45:59 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "command.h"
#include <errno.h>

static void	close_pipe(int fd[2])
{
	if (fd[0] > 0)
		close(fd[0]);
	if (fd[1] > 0)
		close(fd[1]);
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

void pipe_cmd(t_command_group *command_line, int *pid, t_pipe *data_pipe)
{
	int	child;
	int	child_res;

	if (pipe(data_pipe->fd[data_pipe->index % 2]) == -1)
		exit(errno);
	if (command_line->command)
	{
		pid[data_pipe->index] = fork();
		if (pid[data_pipe->index] == 0)
		{
			manage_pipe(data_pipe->fd, data_pipe->index, data_pipe->pipe_count);
			child = execute_command(command_line->command, command_line, data_pipe->fd[data_pipe->index % 2]);
			waitpid(child, &child_res, 0);
			exit(WEXITSTATUS(child_res));
		}
	}
	if (data_pipe->index != 0)
		close_pipe(data_pipe->fd[(data_pipe->index + 1) % 2]);
	if (command_line->pipe_next)
	{
		data_pipe->index++;
		pipe_cmd(command_line->pipe_next, pid, data_pipe);
	}
	close_pipe(data_pipe->fd[data_pipe->index % 2]);
}
