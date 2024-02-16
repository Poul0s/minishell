/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:48:52 by psalame           #+#    #+#             */
/*   Updated: 2024/02/15 23:46:22 by psalame          ###   ########.fr       */
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

char	**ft_strs_insert_str(char **src, char *new_elem, size_t pos)
{
	size_t	i;
	size_t	j;
	char	**res;
	size_t	res_size;

	res_size = ft_strs_len(src) + 1;
	res = malloc((res_size + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (i < res_size)
	{
		if (i == pos)
			res[i] = new_elem;
		else
			res[i] = src[j++];
		i++;
	}
	res[i] = NULL;
	return (res);
}
