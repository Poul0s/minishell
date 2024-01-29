/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:27:28 by psalame           #+#    #+#             */
/*   Updated: 2024/01/29 16:28:05 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_Int.h"

static size_t	operator_get_end(t_string_index *command_line,
								int operator_type)
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
			else if (operator_type == 0
				&& ft_strncmp(command_line->str + end, "||", 2) == 0)
				break ;
			else if (operator_type == 1
				&& ft_strncmp(command_line->str + end, "&&", 2) == 0)
				break ;
		}
		else if (command_line->str[end] == ')' && parenthesis > 0)
			parenthesis--;
		end++;
	}
	return (end);
}

static void	propagate_operator(t_command_group *cmd_grp,
							int operator_type,
							t_command_group *command_fallback)
{
	t_command_group	*tmp;

	while (cmd_grp)
	{
		tmp = cmd_grp;
		if (operator_type == 0)
		{
			while (tmp->on_success && tmp->on_success != command_fallback)
				tmp = tmp->on_success;
			tmp->on_success = command_fallback;
			cmd_grp = cmd_grp->on_error;
		}
		else
		{
			while (tmp->on_error && tmp->on_error != command_fallback)
				tmp = tmp->on_error;
			tmp->on_error = command_fallback;
			cmd_grp = cmd_grp->on_success;
		}
	}
}

static void	parse_operator(t_string_index *command_line,
						t_command_group *cmd_grp,
						int operator_type,
						char ***env)
{
	size_t			end;
	char			end_char;
	t_command_group	*command_fallback;

	command_line->i += 2;
	end = operator_get_end(command_line, operator_type);
	end_char = command_line->str[end];
	command_line->str[end] = 0;
	command_fallback = parse_command_grp(command_line, env);
	propagate_operator(cmd_grp, operator_type, command_fallback);
	command_line->str[end] = end_char;
}

void	parse_command_grp_operators(t_command_group *grp,
									t_string_index *command_line,
									char ***env)
{
	while (command_line->str[command_line->i])
	{
		str_i_skip_spaces(command_line);
		if (command_line->str[command_line->i] == '|'
			&& command_line->str[command_line->i + 1] != '|')
		{
			command_line->i++;
			grp->pipe_next = parse_command_grp(command_line, env);
			continue ;
		}
		str_i_skip_spaces(command_line);
		if (ft_strncmp(command_line->str + command_line->i, "&&", 2) == 0)
		{
			parse_operator(command_line, grp, 0, env);
			continue ;
		}
		str_i_skip_spaces(command_line);
		if (ft_strncmp(command_line->str + command_line->i, "||", 2) == 0)
		{
			parse_operator(command_line, grp, 1, env);
			continue ;
		}
		command_line->i++;
	}
}
