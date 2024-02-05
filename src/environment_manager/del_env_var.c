/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:48:34 by psalame           #+#    #+#             */
/*   Updated: 2024/02/05 18:27:42 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_manager.h"

char	**del_env_var(char **env, char *key)
{
	char	**new_env;
	size_t	i;
	size_t	j;
	size_t	key_len;

	if (!has_env_var(env, key))
		return (env);
	key_len = ft_strlen(key);
	new_env = malloc(ft_strs_len(env) * sizeof(char *));
	i = 0;
	j = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) != 0
			|| (env[i][key_len] != '=' && env[i][key_len] != 0))
		{
			new_env[j] = env[i];
			j++;
		}
		else
			free(env[i]);
		i++;
	}
	new_env[j] = NULL;
	free(env);
	return (new_env);
}
