/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wich_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 03:32:08 by babonnet          #+#    #+#             */
/*   Updated: 2024/02/28 14:20:35 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocompletion.h"

static char	*create_string(const char *start, const char *end)
{
	int		i;
	char	*str;
	int		str_len;

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
	return (str);
}

static t_word	*create_word(const char *start, const char *end)
{
	t_word	*word;
	char	*str;
	char	*mid;

	str = create_string(start, end);
	if (!str)
		return (NULL);
	word = malloc(sizeof(t_word));
	if (!word)
		return (NULL);
	mid = ft_strrchr(str, '/');
	if (!mid)
		mid = ft_strrchr(str, '.');
	if (!mid)
	{
		word->word = str;
		word->path = NULL;
		return (word);
	}
	word->word = ft_strdup(mid + 1);
	mid[1] = 0;
	word->path = ft_strdup(str);
	free(str);
	return (word);
}

t_word	*wich_word(void)
{
	const char	*line;
	const char	*start;
	const char	*end;
	int			cursor;

	line = rl_line_buffer;
	cursor = rl_point;
	start = &line[cursor];
	end = &line[cursor];
	while (start >= line && (ft_isalpha(*start) || *start != '/'))
		start--;
	start++;
	while (*end && (ft_isalpha(*end) || ft_strchr("./", *start)))
		end++;
	return (create_word(start, end));
}
