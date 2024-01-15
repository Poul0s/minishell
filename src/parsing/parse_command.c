/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:36:03 by psalame           #+#    #+#             */
/*   Updated: 2024/01/15 17:08:40 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	parse_variable(char *argument, char *command_line, size_t *i, t_current_focus *focus)
{
	size_t	start;
	size_t	end;

	start = *i;
	end = *i;
	while (command_line[end])
	{
		if (command_line[end] == '"')
			break;
	}
}

static char	*parse_argument(char *command_line)
{
	size_t			start;
	size_t			i;
	char			*argument;
	t_current_focus	focus;

	i = 0;
	argument = NULL;
	while (command_line[i])
	{
		if (command_line[i] == '\'')
			focus.quote = !focus.quote;
		else if (command_line[i] == '$' && !focus.quote)
		{
			parse_variable(argument, command_line, &i, &focus);
		}
		else if (command_line[i] == '"' && !focus.quote)
		{
			
		}
		else if (!focus.quote && !focus.dbl_quote && false) // arg end
			break ;
		else
			ft_strfjoin(argument, command_line[i]);
		
	}
	return (argument);
}

void	parse_command(char *command_line, t_command *command)
{
}