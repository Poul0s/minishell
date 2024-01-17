/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_strs_to_env_data.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:39:52 by psalame           #+#    #+#             */
/*   Updated: 2024/01/17 18:15:44 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_manager.h"

static t_env_data	*convert_str_to_env_data(char *env_var)
{
	t_env_data	*res;
	size_t		separator_index;
	
	if (!env_var)
		return (NULL);
	res = malloc(sizeof(t_env_data));
	if (!res)
		return (NULL);
	separator_index = env_var - ft_strchr(env_var, '=');
	res->key = ft_substr(env_var, 0, separator_index);
	res->value = ft_substr(env_var, separator_index + 1, ft_strlen(env_var));
	res->next = NULL;
	return (res);
}

t_env_data	*convert_strs_to_env_data(char **env)
{
	t_env_data	*parent;
	t_env_data	*prev;
	t_env_data	*current;

	parent = NULL;
	prev = NULL;
	current = NULL;
	if (env)
	{
		while (*env)
		{
			if (current)
				prev = current;
			current = convert_str_to_env_data(*env++);
			if (prev)
				prev->next = current;
			else
				parent = current;
		}
	}
	return (parent);
}
