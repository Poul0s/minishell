/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:23:43 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/21 21:15:32 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <errno.h>

int	execute_command(t_command *command, t_command_group *group_data, int fd[2])
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
		if (command->executable == NULL)
			exit(127);
		execve(command->executable, command->arguments, convert_env_data_to_strs(group_data->env->env)); // todo add premake of char **env in t_env_data for free at end
		exit(errno);
	}
	else if (group_data->on_success || group_data->on_error)
	{
		waitpid(child_pid, &child_pid_res, 0);
		baby_pid = fork();
		if (baby_pid == 0)
		{
			child_pid_res = WEXITSTATUS(child_pid_res);
			if (child_pid_res != 0 && group_data->on_error != NULL)
					exit(execute_command_line(group_data->on_error));
			else
				if (child_pid_res == 0 && group_data->on_success != NULL)
					exit(execute_command_line(group_data->on_success));
			exit(child_pid_res);
		}
		else
			return (baby_pid);
	}
	return (child_pid);
}
