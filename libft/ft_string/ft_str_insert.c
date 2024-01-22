/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_insert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:55:15 by psalame           #+#    #+#             */
/*   Updated: 2024/01/22 17:50:56 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_insert(char *src, char *str, size_t pos)
{
	char	*dest;
	size_t	dest_len;
	size_t	i;

	dest_len = ft_strlen(src) + ft_strlen(str) + 1;
	dest = malloc(dest_len * sizeof(char));
	if (!dest)
		return (dest);
	dest[0] = 0;
	i = 0;
	if (pos < ft_strlen(src))
	{
		ft_strlcat(dest, src, pos + 1);
		ft_strlcat(dest, str, dest_len);
		ft_strlcat(dest, src + pos, dest_len);
	}
	else
	{
		ft_strlcat(dest, src, dest_len);
		ft_strlcat(dest, str, dest_len);
	}
	return (dest);
}
