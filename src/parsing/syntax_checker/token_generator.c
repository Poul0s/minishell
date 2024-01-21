/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_generator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:19:02 by psalame           #+#    #+#             */
/*   Updated: 2024/01/21 17:29:46 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

char	*token_to_str(char c, int token_size)
{
	char	*res;
	int		i;

	res = malloc((token_size + 1) * sizeof(char));
	if (res)
	{
		i = 0;
		while (i < token_size)
		{
			res[i] = c;
			i++;
		}
		res[i] = 0;
	}
	return (res);
}

static inline bool	is_token(char c)
{
	if (c == '&' || c == '|' || c == '>' || c == '<' || c == '(' || c == ')')
		return (true);
	return (false);
}

char	*get_unexpected_token(t_string_index *stri)
{
	int	size;

	size = 0;
	while (!is_token(stri->str[stri->i + size]))
		size++;
	return (ft_substr(stri->str, stri->i, size));
}
