/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:17:39 by psalame           #+#    #+#             */
/*   Updated: 2024/01/13 10:52:58 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_putptr_fd(void *ptr, int fd)
{
	char	*res;
	int		len;

	if (ptr == NULL)
		return (ft_putstr_fd("(nil)", fd));
	res = ft_ultoa_base((long long) ptr, FT_HEXA_BASE);
	if (res == NULL)
		return (ft_putptr_fd("(nil)", fd));
	len = ft_putstr_fd("0x", fd) + ft_putstr_fd(res, fd);
	free(res);
	return (len);
}
