/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:48:52 by psalame           #+#    #+#             */
/*   Updated: 2024/01/16 18:39:19 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_Int.h"
#include "minishell.h"

void	str_i_skip_spaces(t_string_index *command_line)
{
	while (command_line->str[command_line->i] == ' ')
		command_line->i++;
}

static size_t	get_cmd_grp_end(t_string_index *command_line, t_command_group *command_group)
{
	int		nb_parenthesis;
	bool	is_in_parenthesis;
	size_t	end;

	str_i_skip_spaces(command_line);
	is_in_parenthesis = command_line->str[command_line->i] == '(';
	if (!is_in_parenthesis)
		return (ft_strlen(command_line->str));
	command_group->env = ft_strs_dup(command_group->env);
	command_line->i++;
	end = command_line->i;
	nb_parenthesis = 0;
	while (command_line->str[end])
	{
		if (command_line->str[end] == '(')
			nb_parenthesis++;
		else if (command_line->str[end] == ')' && nb_parenthesis != 0)
			nb_parenthesis--;
		else if (command_line->str[end] == ')' && nb_parenthesis == 0)
			break ;
		end++;
	}
	return (end);
}

t_command_group	*parse_command_grp(t_string_index *command_line, char **env)
{
	t_command_group	*res;
	char			end_char;
	size_t			end;

	res = ft_calloc(1, sizeof(t_command_group));
	if (!res)
		return (res);
	res->env = env;
	end = get_cmd_grp_end(command_line, res);
	end_char = command_line->str[end];
	command_line->str[end] = 0;
	res->command = parse_commands(command_line, res->env);
	if (!res->command)
	{
		free(res);
		return (NULL);
	}
	str_i_skip_spaces(command_line);
	if (command_line->str[command_line->i] == '|' && command_line->str[command_line->i + 1] != '|')
	{
		command_line->i++;
		res->pipe_next = parse_command_grp(command_line, res->env);
	}
	command_line->str[end] = end_char;
	if (end_char == ')')
		command_line->i++;
	return (res);
}

t_command_group	*parse_cmd_line(char *command_line, char **env)
{
	t_string_index	str;

	str.str = command_line;
	str.i = 0;
	return (parse_command_grp(&str, env));
}
