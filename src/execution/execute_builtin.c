/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 22:36:42 by psalame           #+#    #+#             */
/*   Updated: 2024/01/23 23:18:56 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_command_builtin(char *str)
{
	if (ft_strncmp(str, "cd", 3) == 0)
		return (true);
	else if (ft_strncmp(str, "echo", 5) == 0)
		return (true);
	else if (ft_strncmp(str, "env", 4) == 0)
		return (true);
	else if (ft_strncmp(str, "pwd", 4) == 0)
		return (true);
	else if (ft_strncmp(str, "export", 7) == 0)
		return (true);
	else if (ft_strncmp(str, "unset", 6) == 0)
		return (true);
	else if (ft_strncmp(str, "exit", 5) == 0)
		return (true);
	else
		return (false);
}

int	execute_builtin_command(t_command *command, t_command_group *group_data)
{
	int	command_res;

	if (ft_strncmp(command->executable, "cd", 3) == 0)
		command_res = ft_cd((const char **) command->arguments);
	else if (ft_strncmp(command->executable, "echo", 5) == 0)
		command_res = ft_echo((const char **) (command->arguments + 1));
	else if (ft_strncmp(command->executable, "env", 4) == 0)
		command_res = ft_env((const char **) convert_env_data_to_strs(group_data->env->env));
	else if (ft_strncmp(command->executable, "pwd", 4) == 0)
		command_res = ft_pwd();
	else if (ft_strncmp(command->executable, "export", 7) == 0)
		command_res = ft_cd((const char **) command->arguments);
	else if (ft_strncmp(command->executable, "unset", 6) == 0)
		command_res = ft_cd((const char **) command->arguments);
	else if (ft_strncmp(command->executable, "exit", 5) == 0)
		command_res = ft_cd((const char **) command->arguments);
	else
		command_res = 127;
	command_res = -command_res - 1;
	return (command_res);
}

// child_pid = execute_builtin_command(command, group_data);