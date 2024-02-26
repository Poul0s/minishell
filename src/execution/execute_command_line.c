/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:02:32 by psalame           #+#    #+#             */
/*   Updated: 2024/02/26 14:14:53 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "execution.h"
#include "minishell.h"
#include <errno.h>
#include <unistd.h>

int	count_pipe(t_command_group *command_line)
{
	int	i;

	i = 0;
	while (command_line)
	{
		command_line = command_line->pipe_next;
		i++;
	}
	return (i);
}

static int	execute_piped_cmd_line(t_command_group *command_line,
									t_execution_data exec_data)
{
	t_pipe	data_pipe;
	int		last_pid_res;
	int		i;

	data_pipe.index = 0;
	data_pipe.pipe_count = count_pipe(command_line);
	exec_data.pid = malloc(data_pipe.pipe_count * sizeof(int));
	if (exec_data.pid == NULL)
	{
		ft_dprintf(2, "%s: %s\n", exec_data.shell_data->exec_name,
			strerror(ENOMEM));
		return (ENOMEM);
	}
	pipe_cmd(command_line, exec_data, &data_pipe);
	i = -1;
	while (++i < data_pipe.pipe_count)
	{
		if (exec_data.pid[i] > 0)
			waitpid(exec_data.pid[i], &last_pid_res, 0);
	}
	if (exec_data.pid[data_pipe.pipe_count - 1] <= 0)
		last_pid_res = (-exec_data.pid[data_pipe.pipe_count - 1] - 1) << 8;
	last_pid_res = WEXITSTATUS(last_pid_res);
	free(exec_data.pid);
	return (last_pid_res);
}

int	execute_command_line(t_command_group *command_line,
		t_execution_data exec_data)
{
	int		last_pid_res;
	bool	forked;

	forked = exec_data.forked;
	exec_data.forked = false;
	exec_data.pid = NULL;
	if (command_line->pipe_next == NULL)
	{
		command_line->command->exec_data = exec_data;
		last_pid_res = execute_command(command_line->command, command_line,
				NULL);
	}
	else
		last_pid_res = execute_piped_cmd_line(command_line, exec_data);
	while (command_line->pipe_next)
		command_line = command_line->pipe_next;
	exec_data.forked = forked;
	if (forked)
	{
		free_shell_data(exec_data.shell_data, false);
		free_command_line(exec_data.base_command_line, false);
		free_command_line(NULL, true);
	}
	return (last_pid_res);
}
