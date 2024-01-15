/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:32:27 by psalame           #+#    #+#             */
/*   Updated: 2023/11/19 17:56:40 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	chr;

	if (s == NULL)
		return (NULL);
	chr = (char) c;
	i = 0;
	while (s[i] != 0 && s[i] != chr)
		i++;
	if (s[i] == chr)
		return ((char *)s + i);
	return (NULL);
}
