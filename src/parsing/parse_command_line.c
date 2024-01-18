/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:48:52 by psalame           #+#    #+#             */
/*   Updated: 2024/01/17 20:59:53 by psalame          ###   ########.fr       */
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
	command_group->env = create_env_tree_children(command_group->env);
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

static void	parse_operator(t_string_index *command_line, t_command_group *cmd_grp, int operator_type)
{
	size_t	end;
	char	end_char;

	command_line->i += 2;
	end = operator_get_end(command_line, operator_type);
	end_char = command_line->str[end];
	command_line->str[end] = 0;
	if (operator_type == 0)
		cmd_grp->on_success = parse_command_grp(command_line, cmd_grp->env);
	else
		cmd_grp->on_error = parse_command_grp(command_line, cmd_grp->env);
	command_line->str[end] = end_char;
}

t_command_group	*parse_command_grp(t_string_index *command_line, t_env_tree *env)
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
	// bug (cmd1 && cmd2) | res : cmd grp stop at end of parenthesis
	// idea : maybe loop operators connectors and stop : at first closed parenthesis if grp not in parenthesis else stop at second parenthesis
	// idea2: loop pipe and operators and stop at end but end must be calculated in consideration pipe and operators
	if (command_line->str[command_line->i] == '|' && command_line->str[command_line->i + 1] != '|')
	{
		command_line->i++;
		res->pipe_next = parse_command_grp(command_line, res->env);
	}
	str_i_skip_spaces(command_line);
	if (ft_strncmp(command_line->str + command_line->i, "&&", 2) == 0)
		parse_operator(command_line, res, 0);
	str_i_skip_spaces(command_line);
	if (ft_strncmp(command_line->str + command_line->i, "||", 2) == 0)
		parse_operator(command_line, res, 1);
	command_line->str[end] = end_char;
	if (end_char == ')')
		command_line->i++;
	return (res);
}

t_command_group	*parse_cmd_line(char *command_line, t_env_tree *env)
{
	t_string_index	str;

	str.str = command_line;
	str.i = 0;
	return (parse_command_grp(&str, env));
}
