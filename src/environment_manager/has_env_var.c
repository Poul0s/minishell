/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:45:01 by psalame           #+#    #+#             */
/*   Updated: 2024/02/05 18:26:28 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_manager.h"

bool	has_env_var(char **env, char *key)
{
	int		i;
	size_t	key_len;

	i = 0;
	key_len = ft_strlen(key);
	if (!env || key_len == 0)
		return (false);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0
			&& (env[i][key_len] == '=' || env[i][key_len] == 0))
			return (true);
		i++;
	}
	return (false);
}
