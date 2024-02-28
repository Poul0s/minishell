/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_first.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 00:33:17 by babonnet          #+#    #+#             */
/*   Updated: 2024/02/28 19:37:38 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocompletion_bonus.h"

int	is_first(void)
{
	char	*line;
	int		pos;

	line = rl_line_buffer;
	pos = rl_point - 1;
	while (pos >= 0 && ft_isalpha(line[pos]))
		pos--;
	while (pos >= 0 && !ft_strchr("|&", line[pos]))
	{
		if (ft_isalpha(line[pos]))
			return (0);
		pos--;
	}
	return (1);
}
