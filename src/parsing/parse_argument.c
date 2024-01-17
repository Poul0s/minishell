/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 00:12:07 by psalame           #+#    #+#             */
/*   Updated: 2024/01/17 13:53:28 by psalame          ###   ########.fr       */
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

static void	insert_variable_data(char **argument, char *var_name, t_list **prev_arguments)
{
	char	*var_res;
	char	**var_res_list;
	size_t	i;

	if (var_name)
	{
		var_res = getenv(var_name);
		free(var_name);
		if (!prev_arguments)
		{
			*argument = ft_strfjoin(*argument, var_res);
			return ;
		}
		var_res_list = ft_split(var_res, ' ');
		if (!var_res_list)
		{
			*argument = ft_strfjoin(*argument, var_res);
			return ;
		}
		i = 0;
		while (var_res_list[i] && var_res_list[i + 1])
			ft_lstadd_back(prev_arguments, ft_lstnew(var_res_list[i++])); // todo free arg if lstnew fail
		*argument = ft_strfjoin(*argument, var_res_list[i]);
		free(var_res_list[i]);
		free(var_res_list);
	}
}

static void	parse_variable(char **argument, t_string_index *command_line, t_list **prev_arguments)
{
	size_t	start;
	size_t	end;
	char	*var_name;

	start = command_line->i + 1;
	end = command_line->i + 1;
	while (command_line->str[end])
	{
		if (!ft_isalnum(command_line->str[end]))
			break;
		end++;
	}
	command_line->i = end;
	if (end == start && is_end_arg(command_line, true))
		*argument = ft_strdup("$");
	else
	{
		var_name = ft_substr(command_line->str, start, end - start);
		insert_variable_data(argument, var_name, prev_arguments);
	}
	command_line->i = end - 1;
}

char	*parse_argument(t_string_index *command_line, t_command *cmd, t_list **prev_arguments)
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
			parse_variable(&argument, command_line, prev_arguments);
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