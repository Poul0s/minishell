/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:39:16 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/29 16:43:50 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	is_valid_flag(const char *flag)
{
	if (!flag)
		return (false);
	if (!ft_strncmp(flag, "-n", 3))
		return (true);
	return (false);
}

int	ft_echo(const char **strs)
{
	bool	n_flag;

	if (!strs)
		return (1);
	n_flag = false;
	while (*strs && is_valid_flag(*strs))
	{
		n_flag = true;
		strs++;
	}
	while (*strs)
	{
		ft_printf("%s", *strs);
		strs++;
		if (*strs)
			ft_putstr_fd(" ", 1);
	}
	if (!n_flag)
		ft_putstr_fd("\n", 1);
	return (0);
}
