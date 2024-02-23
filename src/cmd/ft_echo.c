/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:39:16 by babonnet          #+#    #+#             */
/*   Updated: 2024/02/16 19:41:57 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	is_valid_flag(const char *flag)
{
	const char	*tmp;

	if (!flag)
		return (false);
	tmp = flag;
	if (*tmp != '-')
		return (false);
	tmp++;
	while (*tmp && *tmp == 'n')
		tmp++;
	if (*tmp != 0)
		return (false);
	return (true);
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
