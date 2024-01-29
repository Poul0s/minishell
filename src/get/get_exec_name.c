/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:45:05 by psalame           #+#    #+#             */
/*   Updated: 2024/01/29 14:49:02 by psalame          ###   ########.fr       */
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
