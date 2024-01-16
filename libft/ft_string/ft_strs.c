/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:48:52 by psalame           #+#    #+#             */
/*   Updated: 2024/01/16 18:49:10 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

void	ft_free_strs(char **strs)
{
	size_t	i;

	if (strs)
	{
		i = 0;
		while (strs[i])
		{
			free(strs[i]);
			i++;
		}
		free(strs);
	}
}

size_t	ft_strs_len(char **strs)
{
	size_t	i;

	i = 0;
	if (strs)
	{
		while (*strs++)
			i++;
	}
	return (i);
}

char	**ft_strs_dup(char **src)
{
	char	**dest;
	size_t	dest_len;
	size_t	i;

	dest_len = ft_strs_len(src);
	dest = malloc((dest_len + 1) * sizeof(char *));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < dest_len)
	{
		dest[i] = ft_strdup(src[i]);
		if (!dest[i])
		{
			ft_free_strs(dest);
			return (NULL);
		}
		i++;
	}
	dest[i] = NULL;
	return (dest);
}
