/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 00:12:07 by psalame           #+#    #+#             */
/*   Updated: 2024/01/23 20:50:10 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_Int.h"

static char	*ft_strfjoin_chr(char *s1, char c)
{
	char	*newstr;
	size_t	newlen;
	size_t	i;
	size_t	j;

	newlen = ft_strlen(s1) + 1;
	newstr = malloc((newlen + 1) * sizeof(char));
	if (newstr == NULL)
		return (NULL);
	newstr[newlen] = 0;
	i = 0;
	j = 0;
	if (s1)
	{
		while (s1[i])
			newstr[j++] = s1[i++];
		free(s1);
	}
	newstr[j] = c;
	return (newstr);
}

static bool	is_end_arg(t_string_index *command_line, bool stop_file_redirect)
{
	if (command_line->str[command_line->i] == '|'
		|| command_line->str[command_line->i] == '&'
		|| command_line->str[command_line->i] == ')'
		|| command_line->str[command_line->i] == ' ')
		return (true);
	if (stop_file_redirect)
	{
		if (command_line->str[command_line->i] == '<'
			|| command_line->str[command_line->i] == '>')
			return (true);
	}
	return (false);
}

static void	parse_variable(char **argument,
							t_string_index *command_line,
							t_list **prev_arguments,
							t_command *command) // t_env_tree *env
{
	size_t	start;
	size_t	end;
	char	*var_name;
	t_list	*var_arg_node;

	start = command_line->i + 1;
	end = command_line->i + 1;
	while (command_line->str[end])
	{
		if (!ft_isalnum(command_line->str[end]) && (command_line->str[end] != '?' || end != start))
			break ;
		end++;
	}
	command_line->i = end;
	if (end == start && is_end_arg(command_line, true)) // why condition && is_end_arg ??
		*argument = ft_strdup("$");
	else
	{
		var_name = ft_substr(command_line->str, start, end - start);
		var_arg_node = insert_variable_argument(argument, prev_arguments, var_name, ENVIRONMENT_VARIABLE);
		ft_lstadd_back(&(command->argument_variables), var_arg_node);
	}
	command_line->i = end - 1;
}

static void	parse_wildcard(char **argument, t_list **prev_arguments, t_command *command)
{
	t_list	*var_arg_node;

	var_arg_node = insert_variable_argument(argument, prev_arguments, NULL, WILDCARD);
	ft_lstadd_back(&(command->argument_variables), var_arg_node);
}

char	*parse_argument(t_string_index *command_line,
						t_command *cmd,
						t_list **prev_arguments,
						t_env_tree *env)
{
	char			*argument;
	t_current_focus	foc;
	char			c;

	ft_bzero(&foc, sizeof(t_current_focus));
	str_i_skip_spaces(command_line);
	argument = NULL;
	while (command_line->str[command_line->i])
	{
		c = command_line->str[command_line->i];
		if (c == '\'' && !foc.dblquote)
		{
			foc.quote = !foc.quote;
			argument = ft_strfjoin(argument, "");
		}
		else if (c == '$' && !foc.quote)
			parse_variable(&argument, command_line, prev_arguments, cmd); // env
		else if (c == '"' && !foc.quote)
		{
			foc.dblquote = !foc.dblquote;
			argument = ft_strfjoin(argument, "");
		}
		else if (c == '*' && !foc.quote && !foc.dblquote)
			parse_wildcard(&argument, prev_arguments, cmd);
		else if (!foc.quote && !foc.dblquote && is_end_arg(command_line, !cmd))
			break ;
		else if (c == '<' || c == '>')
			parse_file_redirection(command_line, &argument, cmd, env);
		else
			argument = ft_strfjoin_chr(argument, c);
		command_line->i++;
	}
	return (argument);
}
