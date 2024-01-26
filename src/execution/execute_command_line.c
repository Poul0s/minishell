/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:02:32 by psalame           #+#    #+#             */
/*   Updated: 2024/01/26 17:07:40 by psalame          ###   ########.fr       */
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
		if (command_line->pipe_next == NULL) // todo move mayeb bad pos
			command_line->command->last_pipe_cmd = true;
		command_line = command_line->pipe_next;
		i++;
	}
	return (i);
}

int	execute_command_line(t_command_group *command_line, t_execution_data exec_data)
{
	t_pipe	data_pipe;
	int		*pid;
	int		last_pid_res;
	int		i;

	data_pipe.index = 0;
	data_pipe.pipe_count = count_pipe(command_line);
	pid = malloc(data_pipe.pipe_count * sizeof(int));
	exec_data.pid = pid;
	if (data_pipe.pipe_count == 1 && !command_line->is_in_parenthesis)
	{
		command_line->command->exec_data = exec_data;
		pid[0] = execute_command(command_line->command, command_line, NULL);
	}
	else
		pipe_cmd(command_line, exec_data, &data_pipe);
	// if (pid[data_pipe.pipe_count - 1] > 0 && waitpid(pid[data_pipe.pipe_count - 1], &last_pid_res, 0) == -1)
	// {
	// 	free(pid);
	// 	return (-1);
	// }
	// else
	{
		i = 0;
		while (i < data_pipe.pipe_count)
		{
			if (pid[i] > 0)
				waitpid(pid[i], &last_pid_res, 0);
			i++;
		}
		if (pid[data_pipe.pipe_count - 1] <= 0)
			last_pid_res = (-pid[data_pipe.pipe_count - 1] - 1) >> 8;
		else if (!WIFEXITED(last_pid_res))
		{
			if ((WCOREDUMP(last_pid_res)))
			{
				ft_dprintf(2, "Quit (core dumped)\n");
				last_pid_res = 131 << 8;
			}
			else
			{
				ft_dprintf(2, "\n");
				last_pid_res = 130 << 8;
			}
		}
		free(pid);
		while (command_line->pipe_next)
			command_line = command_line->pipe_next;
		if (WEXITSTATUS(last_pid_res) == 0 && command_line->on_success)
			return (execute_command_line(command_line->on_success, exec_data));
		else if (WEXITSTATUS(last_pid_res) != 0 && command_line->on_error)
			return (execute_command_line(command_line->on_success, exec_data));
		else
			return (WEXITSTATUS(last_pid_res));
	}
}
