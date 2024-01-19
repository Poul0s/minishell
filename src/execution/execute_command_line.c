/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:02:32 by psalame           #+#    #+#             */
/*   Updated: 2024/01/19 17:32:02 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

// find_cmd
// fork() if not built-in
// child1->execve cmd
// parent1->if succ or error defined
//         fork()
//          child2->waitpid(child)
//                  execute_command_line(group_data->on_success || group_data->on_error)
static int	execute_command(t_command *command, t_command_group *group_data)
{
	int		child_pid;
	int		baby_pid;
	int		child_pid_res;

	baby_pid = -1;
	child_pid = fork();
	if (child_pid == 0)
	{
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

int	execute_command_line(t_command_group *command_line)
{
	int	child;

	child = execute_command(command_line->command, command_line);
	if (command_line->pipe_next)
		execute_command_line(command_line->pipe_next);
	else
		waitpid(child, NULL, 0);
	return (0);
}
