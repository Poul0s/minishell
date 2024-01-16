/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:43:44 by psalame           #+#    #+#             */
/*   Updated: 2024/01/16 18:40:00 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_Int.h"
#include "minishell.h"

static size_t	operator_get_end(t_string_index *command_line, int operator_type)
{
	int		parenthesis;
	size_t	end;

	parenthesis = 0;
	end = command_line->i;
	while (command_line->str[end])
	{
		if (parenthesis == 0)
		{
			if (command_line->str[end] == '(')
				parenthesis++;
			else if (command_line->str[end] == ')')
				break ;
			else if (command_line->str[end] == '|' && command_line->str[end + 1] != '|')
				break ;
			else if (operator_type == 0 && !ft_strncmp(command_line->str + end, "||", 2))
				break ;
			else if (operator_type == 1 && !ft_strncmp(command_line->str + end, "&&", 2))
				break ;
		}
		else if (command_line->str[end] == ')' && parenthesis > 0)
			parenthesis--;
		end++;
	}
	return (end);
}

static void	parse_operator(t_string_index *command_line, t_command *cmd, int operator_type, char **env)
{
	size_t	end;
	char	end_char;

	command_line->i += 2;
	end = operator_get_end(command_line, operator_type);
	end_char = command_line->str[end];
	command_line->str[end] = 0;
	if (operator_type == 0)
		cmd->on_success = parse_command_grp(command_line, env);
	else
		cmd->on_error = parse_command_grp(command_line, env);
	command_line->str[end] = end_char;
}

t_command	*parse_commands(t_string_index *command_line, char **env)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (cmd);
	parse_command(command_line, cmd);
	if (cmd->executable == NULL)
	{
		free(cmd);
		cmd = NULL;
	}
	str_i_skip_spaces(command_line);
	if (ft_strncmp(command_line->str + command_line->i, "&&", 2) == 0)
		parse_operator(command_line, cmd, 0, env);
	str_i_skip_spaces(command_line);
	if (ft_strncmp(command_line->str + command_line->i, "||", 2) == 0)
		parse_operator(command_line, cmd, 1, env);
	return (cmd);
}
