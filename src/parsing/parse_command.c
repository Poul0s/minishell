/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:36:03 by psalame           #+#    #+#             */
/*   Updated: 2024/01/15 18:52:30 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_Int.h"
#include "minishell.h"

static char	*ft_strfjoinc(char *s1, char c)
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

static void	parse_variable(char *argument, t_string_index *command_line, t_current_focus *focus)
{
	size_t	start;
	size_t	end;
	char	*var_name;
	char	*var_res;

	start = command_line->i + 1;
	end = command_line->i + 1;
	while (command_line->str[end])
	{
		if (command_line->str[end] == '"')
			break;
		if (command_line->str[end] == '\'')
			break;
		if (command_line->str[end] == ' ')
			break;
		// todo complete
		end++;
	}
	var_name = ft_substr(command_line->str, start, end - start);
	if (var_name)
	{
		var_res = getenv(var_name);
		free(var_name);
		ft_strfjoin(argument, var_res);
	}
	command_line->i = end;
}

static inline bool	*is_end_arg(t_string_index *command_line)
{
	if (command_line->str[command_line->i] == '|' ||
		command_line->str[command_line->i] == '&' ||
		command_line->str[command_line->i] == ';' ||
		command_line->str[command_line->i] == ')' ||
		command_line->str[command_line->i] == ' ')
		return (true);
	return (false);
}

static char	*parse_argument(t_string_index *command_line)
{
	size_t			start;
	char			*argument;
	t_current_focus	focus;
	char			c;

	ft_bzero(&focus, sizeof(t_current_focus));
	argument = NULL;
	while (command_line->str[command_line->i])
	{
		c = command_line->str[command_line->i];
		if (c == '\'' && !focus.dbl_quote)
			focus.quote = !focus.quote;
		else if (c == '$' && !focus.quote)
			parse_variable(argument, command_line, &focus);
		else if (c == '"' && !focus.quote)
			focus.dbl_quote = !focus.dbl_quote;
		else if (!focus.quote && !focus.dbl_quote && is_end_arg(command_line)) // arg end
			break ;
		else
			ft_strfjoin(argument, c);
		
	}
	return (argument);
}

void	parse_command(t_string_index *command_line, t_command *command)
{
	t_list	*arguments;
	char	*argument;
	size_t	i;

	while (command_line->str[command_line->i] == ' ')
		command_line->i++;
	arguments = NULL;
	argument = parse_argument(command_line);
	while (argument)
	{
		ft_lstadd_back(&arguments, ft_lstnew(argument));
		argument = parse_argument(command_line);
	}
	if (ft_lstsize(arguments) == 0)
		return ;
	command->executable = arguments->content;
	command->arguments = malloc((ft_lstsize(arguments) + 1) * sizeof(char *));
	if (!command->arguments)
		return ;
	i = 0;
	while (arguments)
	{
		command->arguments[i++] = arguments->content;
		arguments = arguments->next;
	}
	command->arguments[i] = 0;
}

// todo parse infile outfile heredocuments
