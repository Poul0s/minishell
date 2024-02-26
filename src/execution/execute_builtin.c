/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 22:36:42 by psalame           #+#    #+#             */
/*   Updated: 2024/02/26 14:59:56 by psalame          ###   ########.fr       */
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

static t_builtin_function	get_builtin_function(char *executable)
{
	if (ft_strncmp(executable, "cd", 3) == 0)
		return (&ft_cd);
	else if (ft_strncmp(executable, "echo", 5) == 0)
		return (&ft_echo);
	else if (ft_strncmp(executable, "env", 4) == 0)
		return (&ft_env);
	else if (ft_strncmp(executable, "pwd", 4) == 0)
		return (&ft_pwd);
	else if (ft_strncmp(executable, "export", 7) == 0)
		return (&ft_export);
	else if (ft_strncmp(executable, "unset", 6) == 0)
		return (&ft_unset);
	else if (ft_strncmp(executable, "exit", 5) == 0)
		return (&ft_exit);
	else
		return (NULL);
}

int	execute_builtin_command(t_command *command)
{
	int					command_res;
	int					in;
	int					out;
	t_builtin_function	fct;

	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	manage_infile(command->infiles, STDIN_FILENO);
	manage_outfile(command->outfiles, STDOUT_FILENO);
	fct = get_builtin_function(command->executable);
	if (fct)
		command_res = fct(command);
	else
		command_res = 127;
	command_res = -command_res - 1;
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	return (command_res);
}
