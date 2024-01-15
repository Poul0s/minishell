/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:43:44 by psalame           #+#    #+#             */
/*   Updated: 2024/01/15 20:10:59 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_Int.h"
#include "minishell.h"

t_command	*parse_commands(t_string_index *command_line)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (cmd);
	parse_command(cmd, command_line);
	if (cmd->executable == NULL)
	{
		free(cmd);
		cmd = NULL;
	}
	str_i_skip_spaces(command_line);
	// todo add depth for && and || combinaison : '||' will replace on cmd not on on_success
	if (ft_strncmp(command_line->str + command_line->i, "&&", 2) == 0)
	{
		command_line->i += 2;
		cmd->on_success = parse_command_grp(command_line);
	}
	else if (ft_strncmp(command_line->str + command_line->i, "||", 2) == 0)
	{
		command_line->i += 2;
		cmd->on_success = parse_command_grp(command_line);
	}
	return (cmd);
}
