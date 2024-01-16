/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:39:16 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/16 15:35:13 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

int	ft_echo(const char **strs)
{
	bool	n_flag;

	if (!strs)
		return (1);
	n_flag = true;
	if (*strs && *strs[0] == '-')
	{
		if (!ft_strncmp(*strs, "-n", ft_strlen(*strs) + 1))
		{
			n_flag = false;
			strs++;
		}
		else if ((*strs)[1] == 0)
			strs++;
	}
	while (*strs)
	{
		ft_printf("%s", *strs);
		strs++;
		if (*strs)
			ft_putstr_fd(" ", 1);
	}
	if (n_flag)
		ft_putstr_fd("\n", 1);
	return (0);
}
