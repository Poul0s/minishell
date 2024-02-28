/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 00:12:07 by psalame           #+#    #+#             */
/*   Updated: 2024/02/28 19:37:39 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_Int_bonus.h"

static bool	is_end_arg(t_string_index *command_line, bool stop_file_redirect)
{
	if (command_line->str[command_line->i] == '|'
		|| command_line->str[command_line->i] == '&'
		|| command_line->str[command_line->i] == ')'
		|| command_line->str[command_line->i] == ' '
		|| command_line->str[command_line->i] == 0)
		return (true);
	if (stop_file_redirect)
	{
		if (command_line->str[command_line->i] == '<'
			|| command_line->str[command_line->i] == '>')
			return (true);
	}
	return (false);
}

static void	parse_variable(t_current_focus *foc, t_string_index *cmd_line,
		t_list **prev_args, t_command *command)
{
	size_t	start;
	size_t	end;
	char	*var_name;
	t_list	*var_arg_node;

	start = cmd_line->i + 1;
	end = cmd_line->i;
	while (cmd_line->str[++end])
	{
		if ((end != start && cmd_line->str[start] == '?')
			|| (!is_var_arg_char_correct(cmd_line, start, end)
				&& (cmd_line->str[end] != '?' || end != start)))
			break ;
	}
	cmd_line->i = end;
	if (end == start && (is_end_arg(cmd_line, true)
			|| (cmd_line->str[end] == '"' && foc->dblquote)))
		foc->data = ft_strfjoin_chr(foc->data, '$');
	else
	{
		var_name = ft_substr(cmd_line->str, start, end - start);
		var_arg_node = insert_var_arg(foc, prev_args, var_name, ENV_VAR);
		ft_lstadd_back(&(command->argument_variables), var_arg_node);
	}
	cmd_line->i = end - 1;
}

static void	parse_wildcard(t_current_focus *foc, t_list **prev_arguments,
		t_command *command)
{
	t_list	*var_arg_node;

	var_arg_node = insert_var_arg(foc, prev_arguments, NULL, WILDCARD);
	ft_lstadd_back(&(command->argument_variables), var_arg_node);
}

static bool	parse_argument_char(t_string_index *command_line, t_command *cmd,
		t_list **prev_arguments, t_current_focus *foc)
{
	char	c;

	c = command_line->str[command_line->i];
	if (c == '\'' && !foc->dblquote)
	{
		foc->quote = !foc->quote;
		foc->data = ft_strfjoin(foc->data, "");
	}
	else if (c == '$' && !foc->quote)
		parse_variable(foc, command_line, prev_arguments, cmd);
	else if (c == '"' && !foc->quote)
	{
		foc->dblquote = !foc->dblquote;
		foc->data = ft_strfjoin(foc->data, "");
	}
	else if (c == '*' && !foc->quote && !foc->dblquote)
		parse_wildcard(foc, prev_arguments, cmd);
	else if (!foc->quote && !foc->dblquote && is_end_arg(command_line, !cmd))
		return (true);
	else if (!foc->quote && !foc->dblquote && (c == '<' || c == '>'))
		parse_file_redirection(command_line, cmd);
	else
		foc->data = ft_strfjoin_chr(foc->data, c);
	command_line->i++;
	return (false);
}

char	*parse_argument(t_string_index *command_line, t_command *cmd,
		t_list **prev_arguments)
{
	t_current_focus	foc;
	char			c;

	ft_bzero(&foc, sizeof(t_current_focus));
	str_i_skip_spaces(command_line);
	while (command_line->str[command_line->i])
	{
		if (parse_argument_char(command_line, cmd, prev_arguments, &foc))
			break ;
		else if (!(foc.quote) && !(foc.dblquote) && foc.data != NULL)
		{
			c = command_line->str[command_line->i];
			if (c == '<' || c == '>')
				break ;
		}
	}
	return (foc.data);
}
