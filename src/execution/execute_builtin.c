/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 22:36:42 by psalame           #+#    #+#             */
/*   Updated: 2024/02/24 14:14:34 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include <unistd.h>

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

int	execute_builtin_command(t_command *command)
{
	int		command_res;
	char	*exec_name;
	int		in;
	int		out;

	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	manage_infile(command->infiles, STDIN_FILENO);
	manage_outfile(command->outfiles, STDOUT_FILENO);
	exec_name = command->exec_data.shell_data->exec_name;
	if (ft_strncmp(command->executable, "cd", 3) == 0)
		command_res = ft_cd((const char **)command->arguments, command->env);
	else if (ft_strncmp(command->executable, "echo", 5) == 0)
		command_res = ft_echo((const char **)(command->arguments + 1));
	else if (ft_strncmp(command->executable, "env", 4) == 0)
		command_res = ft_env(*((char ***)command->env));
	else if (ft_strncmp(command->executable, "pwd", 4) == 0)
		command_res = ft_pwd();
	else if (ft_strncmp(command->executable, "export", 7) == 0)
		command_res = ft_export(command->arguments, command->env, exec_name);
	else if (ft_strncmp(command->executable, "unset", 6) == 0)
		command_res = ft_unset(command->arguments, command->env);
	else if (ft_strncmp(command->executable, "exit", 5) == 0)
		command_res = ft_exit(command);
	else
		command_res = 127;
	command_res = -command_res - 1;
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	return (command_res);
}

// child_pid = execute_builtin_command(command, group_data);
