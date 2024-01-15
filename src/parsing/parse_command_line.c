/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:48:52 by psalame           #+#    #+#             */
/*   Updated: 2024/01/15 20:09:37 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_Int.h"
#include "minishell.h"

void	str_i_skip_spaces(t_string_index *command_line)
{
	while (command_line->str[command_line->i] == ' ')
		command_line->i++;
}

static t_command_line	*parse_command_grp(t_string_index *command_line)
{
	t_command_line	*res;

	res = ft_calloc(1, sizeof(t_command_line));
	if (!res)
		return (res);
	res->command = parse_commands(command_line);
	if (!res->command)
	{
		free(res);
		return (NULL);
	}
	str_i_skip_spaces(command_line);
	if (command_line->str[command_line->i])
	{
		// todo other function
		char c = command_line->str[command_line->i];
		if (c == ';')
		{
			command_line->i++;
			res->next = parse_command_grp(command_line);
		}
		else if (c == '|')
		{
			command_line->i++;
			res->pipe_next = parse_command_grp(command_line);
		}
	}
	return (res);
}

t_command_line	*parse_cmd_line(char *command_line)
{
	t_string_index	str;

	str.str = command_line;
	str.i = 0;
	return (parse_command_grp(&str));
}
