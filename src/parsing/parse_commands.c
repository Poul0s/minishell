/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:43:44 by psalame           #+#    #+#             */
/*   Updated: 2024/01/17 20:32:44 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_Int.h"
#include "minishell.h"

t_command	*parse_commands(t_string_index *command_line, t_env_tree *env)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (cmd);
	parse_command(command_line, cmd, env);
	if (cmd->executable == NULL)
	{
		free(cmd);
		cmd = NULL;
	}
	// todo change name bc not commands anymore
	// str_i_skip_spaces(command_line);
	// if (ft_strncmp(command_line->str + command_line->i, "&&", 2) == 0)
	// 	parse_operator(command_line, cmd, 0, env);
	// str_i_skip_spaces(command_line);
	// if (ft_strncmp(command_line->str + command_line->i, "||", 2) == 0)
	// 	parse_operator(command_line, cmd, 1, env);
	return (cmd);
}
