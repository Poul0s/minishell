/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:02:32 by psalame           #+#    #+#             */
/*   Updated: 2024/01/20 18:39:04 by babonnet         ###   ########.fr       */
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
	t_pipe data_pipe;
	int *pid;

	data_pipe.index = 0;
	data_pipe.pipe_count = count_pipe(command_line);
	pid = malloc(data_pipe.pipe_count * sizeof(int));
	pipe_cmd(command_line, pid, &data_pipe);
	return (0);
}
