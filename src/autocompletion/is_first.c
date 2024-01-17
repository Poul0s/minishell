/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_first.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 00:33:17 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/17 16:36:37 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "autocompleion.h"
#include "ft_string.h"

bool is_first(void)
{
	char *line;

	line = rl_line_buffer;

	ft_printf("\n%d\n", rl_point);
	while(rl_point && ft_isalpha(line[rl_point]))
		rl_point--;
	while(rl_point && !ft_strchr("|&", line[rl_point]))
	{
		if (ft_isalpha(line[rl_point]))
			return (false);
		rl_point--;
	}
	ft_printf("true");
	return (true);
}
