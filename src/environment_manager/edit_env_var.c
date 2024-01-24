/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_env_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:45:33 by psalame           #+#    #+#             */
/*   Updated: 2024/01/24 21:40:53 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**edit_env_var(char **env, char *key, char *new_value)
{
	char	**new_env;
	size_t	i;

	env = del_env_var(env, key);
	new_env = malloc((ft_strs_len(env) + 2) * sizeof(char *));
	i = 0;
	while (env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = NULL;
	new_env[i] = ft_strfjoin(new_env[i], key);
	new_env[i] = ft_strfjoin_chr(new_env[i], '=');
	new_env[i] = ft_strfjoin(new_env[i], new_value);
	new_env[i + 1] = NULL;
	free(env);
	return (new_env);
}
