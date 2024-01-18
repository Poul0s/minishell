/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env_data_to_strs.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:28:50 by psalame           #+#    #+#             */
/*   Updated: 2024/01/18 14:37:34 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_manager.h"

size_t	get_env_data_size(t_env_data *env_data)
{
	size_t	len;

	len = 0;
	while (env_data)
	{
		env_data = env_data->next;
		len++;
	}
	return (len);
}

static char	*convert_env_data_to_str(t_env_data *env_data)
{
	char	*res;
	size_t	res_size;

	res_size = ft_strlen(env_data->key) + 1 + ft_strlen(env_data->value);
	res = malloc((res_size + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[0] = 0;
	ft_strlcat(res, env_data->key, res_size);
	ft_strlcat(res, "=", res_size);
	ft_strlcat(res, env_data->value, res_size);
	return (res);
}

char	**convert_env_data_to_strs(t_env_data *env_data)
{
	char	**res;
	size_t	size;
	size_t	i;

	size = get_env_data_size(env_data);
	if (size == 0)
		return (NULL);
	res = malloc((size + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (env_data)
	{
		res[i] = convert_env_data_to_str(env_data);
		if (!res)
		{
			ft_free_strs(res);
			return (NULL);
		}
		env_data = env_data->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}
