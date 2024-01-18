/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:00:56 by psalame           #+#    #+#             */
/*   Updated: 2024/01/18 22:29:35 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_manager.h"

t_env_data	*get_env_data(t_env_data *env_data, char *key)
{
	size_t		len;

	len = ft_strlen(key);
	while (env_data)
	{
		if (len == ft_strlen(env_data->key))
			if (ft_strncmp(key, env_data->key, len) == 0)
				return (env_data);
		env_data = env_data->next;
	}
	return (NULL);
}

char	*get_env_value(t_env_data *env_data, char *key)
{
	t_env_data	*env_res_object;

	env_res_object = get_env_data(env_data, key);
	if (env_res_object)
		return (env_res_object->value);
	return (NULL);
}
