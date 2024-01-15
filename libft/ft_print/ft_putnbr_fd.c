/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:37:59 by psalame           #+#    #+#             */
/*   Updated: 2023/11/21 17:07:26 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_putnbr_fd(int n, int fd)
{
	unsigned int	un;
	char			c;
	ssize_t			len;

	len = 0;
	if (n < 0)
	{
		len += write(fd, "-", 1);
		un = -n;
	}
	else
		un = n;
	if (un > 9)
		len += ft_putnbr_fd(un / 10, fd);
	c = un % 10 + '0';
	len += write(fd, &c, 1);
	return (len);
}
