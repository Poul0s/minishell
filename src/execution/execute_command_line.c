/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:02:32 by psalame           #+#    #+#             */
/*   Updated: 2024/01/22 13:14:44 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "execution.h"
#include "minishell.h"
#include <errno.h>
#include <unistd.h>

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

int	execute_command_line(t_command_group *command_line)
{
	t_pipe	data_pipe;
	int		*pid;
	int		last_pid_res;
	int		i;

	data_pipe.index = 0;
	data_pipe.pipe_count = count_pipe(command_line);
	pid = malloc(data_pipe.pipe_count * sizeof(int));
	pipe_cmd(command_line, pid, &data_pipe);
	if (waitpid(pid[data_pipe.pipe_count - 1], &last_pid_res, 0) == -1)
		return (-1);
	else
	{
		i = 0;
		while (i < data_pipe.pipe_count - 1)
			waitpid(pid[i++], NULL, 0);
		return (WEXITSTATUS(last_pid_res));
	}
}
