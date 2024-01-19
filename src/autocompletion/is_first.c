/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_first.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 00:33:17 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/18 18:46:28 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocompletion.h"

int	is_first(void)
{
	char	*line;
	int		pos;

	line = rl_line_buffer;
	pos = rl_point - 1;
	while (pos && ft_isalpha(line[pos]))
		pos--;
	while (pos && !ft_strchr("|&", line[pos]))
	{
		if (ft_isalpha(line[pos]))
			return (0);
		pos--;
	}
	return (1);
}
