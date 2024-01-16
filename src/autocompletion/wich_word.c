/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wich_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 03:32:08 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/16 04:15:44 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"
#include "libft.h"
#include "minishell.h"
#include <readline/readline.h>

static char *create_string(const char *start, const char *end)
{
	int i;
	char *str;
	int str_len;

	str_len = end - start;
	str = malloc((str_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < str_len)
	{
		str[i] = start[i];
		i++;
	}
	str[i] = 0;
	//printf("\n%s", str);
	return (str);
}

char	*wich_word(void)
{
	const char	*line;
	const char	*start;
	const char	*end;
	int			cursor;

	line = rl_line_buffer;
	cursor = rl_point;
	if (cursor >= 1)
		cursor--;
	start = &line[cursor];
	end = &line[cursor];
	while(start >= line && ft_isalpha(*start))
		start--;
	start++;
	while(*end && ft_isalpha(*end))
		end++;
	return (create_string(start, end));
}
