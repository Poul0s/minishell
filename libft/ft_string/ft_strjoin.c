/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:03:47 by psalame           #+#    #+#             */
/*   Updated: 2023/11/07 22:17:07 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	size_t	i;
	char	*res;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1len = ft_strlen((char *)s1);
	s2len = ft_strlen((char *)s2);
	res = malloc((s1len + s2len + 1) * sizeof(char));
	if (res == NULL)
		return (res);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i++])
		res[s1len + i - 1] = s2[i - 1];
	res[s1len + s2len] = 0;
	return (res);
}

char	*ft_strfjoin(char *s1, char *s2)
{
	char	*newstr;
	size_t	newlen;
	size_t	i;
	size_t	j;

	newlen = ft_strlen(s1) + ft_strlen(s2);
	newstr = malloc((newlen + 1) * sizeof(char));
	if (newstr == NULL)
		return (NULL);
	newstr[newlen] = 0;
	i = 0;
	j = 0;
	if (s1)
	{
		while (s1[i])
			newstr[j++] = s1[i++];
		free(s1);
	}
	i = 0;
	if (s2)
		while (s2[i])
			newstr[j++] = s2[i++];
	return (newstr);
}
