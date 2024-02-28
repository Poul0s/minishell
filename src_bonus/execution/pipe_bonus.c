/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:19:10 by babonnet          #+#    #+#             */
/*   Updated: 2024/02/28 19:46:30 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_bonus.h"
#include "minishell_bonus.h"
#include <errno.h>

static void	close_pipe(int fd[2])
{
	if (fd[0] > 0)
		close(fd[0]);
	if (fd[1] > 0)
		close(fd[1]);
}

static void	manage_pipe(t_command *cmd, int fd[2][2], int i, int size)
{
	if (i == size - 1)
		manage_infile(cmd->infiles, fd[(i + 1) % 2][0]);
	else if (i == 0)
		manage_outfile(cmd->outfiles, fd[0][1]);
	else
	{
		manage_infile(cmd->infiles, fd[(i + 1) % 2][0]);
		manage_outfile(cmd->outfiles, fd[i % 2][1]);
	}
	close_pipe(fd[0]);
	if (i > 0)
		close_pipe(fd[1]);
}

void	pipe_cmd(t_command_group *command_line, t_execution_data exec_data,
		t_pipe *data_pipe)
{
	int	child_res;

	exec_data.forked = true;
	if (pipe(data_pipe->fd[data_pipe->index % 2]) == -1)
		exit(errno);
	if (command_line->command)
	{
		exec_data.pid[data_pipe->index] = fork();
		if (exec_data.pid[data_pipe->index] == 0)
		{
			manage_pipe(command_line->command, data_pipe->fd, data_pipe->index,
				data_pipe->pipe_count);
			command_line->command->exec_data = exec_data;
			child_res = execute_command(command_line->command, command_line,
					data_pipe->fd[data_pipe->index % 2]);
			exit(child_res);
		}
	}
	if (data_pipe->index != 0)
		close_pipe(data_pipe->fd[(data_pipe->index + 1) % 2]);
	if (command_line->pipe_next)
		data_pipe->index++;
	if (command_line->pipe_next)
		pipe_cmd(command_line->pipe_next, exec_data, data_pipe);
	close_pipe(data_pipe->fd[data_pipe->index % 2]);
}
