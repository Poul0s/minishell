/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 00:12:07 by psalame           #+#    #+#             */
/*   Updated: 2024/01/16 01:43:32 by psalame          ###   ########.fr       */
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

static void	parse_variable(char **argument, t_string_index *command_line)
{
	size_t	start;
	size_t	end;
	char	*var_name;
	char	*var_res;

	start = command_line->i + 1;
	end = command_line->i + 1;
	while (command_line->str[end])
	{
		if (!ft_isalnum(command_line->str[end]))
			break;
		end++;
	}
	var_name = ft_substr(command_line->str, start, end - start);
	if (var_name)
	{
		var_res = getenv(var_name);
		free(var_name);
		*argument = ft_strfjoin(*argument, var_res);
	}
	command_line->i = end - 1;
}

static bool	is_end_arg(t_string_index *command_line, bool stop_file_redirect)
{
	if (command_line->str[command_line->i] == '|' ||
		command_line->str[command_line->i] == '&' ||
		command_line->str[command_line->i] == ')' ||
		command_line->str[command_line->i] == ' ')
		return (true);
	if (stop_file_redirect)
	{
		if (command_line->str[command_line->i] == '<' ||
			command_line->str[command_line->i] == '>')
			return (true);
	}
	return (false);
}

char	*parse_argument(t_string_index *command_line, t_command *cmd)
{
	char			*argument;
	t_current_focus	focus;
	char			c;

	ft_bzero(&focus, sizeof(t_current_focus));
	str_i_skip_spaces(command_line);
	argument = NULL;
	while (command_line->str[command_line->i])
	{
		c = command_line->str[command_line->i];
		if (c == '\'' && !focus.dbl_quote)
			focus.quote = !focus.quote;
		else if (c == '$' && !focus.quote)
			parse_variable(&argument, command_line);
		else if (c == '"' && !focus.quote)
			focus.dbl_quote = !focus.dbl_quote;
		else if (!focus.quote && !focus.dbl_quote && is_end_arg(command_line, !cmd))
			break ;
		else if (c == '<' || c == '>')
			parse_file_redirection(command_line, &argument, cmd);
		else
			argument = ft_strfjoin_chr(argument, c);
		command_line->i++;
	}
	return (argument);
}