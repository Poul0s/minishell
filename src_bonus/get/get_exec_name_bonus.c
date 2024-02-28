/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:45:05 by psalame           #+#    #+#             */
/*   Updated: 2024/02/28 19:37:38 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_exec_name(char *bin_path)
{
	char	*res;

	if (bin_path == NULL)
		res = ft_strdup("minishell");
	else
	{
		res = ft_strrchr(bin_path, '/');
		if (res == NULL)
			res = ft_strdup(bin_path);
		else
			res = ft_strdup(res + 1);
	}
	return (res);
}
