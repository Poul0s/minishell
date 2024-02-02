/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_group.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:27:56 by psalame           #+#    #+#             */
/*   Updated: 2024/02/02 20:17:06 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_Int.h"

static size_t	get_cmd_grp_end(t_string_index *command_line)
{
	int		nb_parenthesis;
	bool	is_in_parenthesis;
	size_t	end;

	str_i_skip_spaces(command_line);
	is_in_parenthesis = command_line->str[command_line->i] == '(';
	if (!is_in_parenthesis)
		return (ft_strlen(command_line->str));
	command_line->i++;
	end = command_line->i;
	nb_parenthesis = 1;
	while (command_line->str[end])
	{
		if (command_line->str[end] == '(')
			nb_parenthesis++;
		else if (command_line->str[end] == ')' && nb_parenthesis == 0)
			break ;
		else if (command_line->str[end] == ')')
			nb_parenthesis--;
		end++;
	}
	return (end);
}

t_command_group	*parse_command_grp(t_string_index *command_line, char ***env)
{
	t_command_group	*res;
	char			end_char;
	size_t			end;

	res = ft_calloc(1, sizeof(t_command_group));
	if (!res)
		return (res);
	end = get_cmd_grp_end(command_line);
	end_char = command_line->str[end];
	command_line->str[end] = 0;
	while (command_line->str[command_line->i] == ' '
		|| command_line->str[command_line->i] == '(')
		command_line->i++;
	res->command = parse_command(command_line, env);
	if (!res->command)
	{
		free(res);
		return (NULL);
	}
	parse_command_grp_operators(res, command_line, env);
	command_line->str[end] = end_char;
	return (res);
}
