/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:32:24 by psalame           #+#    #+#             */
/*   Updated: 2024/01/17 17:27:37 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_manager.h"

static void	del_env_var_childrens(t_env_tree *env_tree, char *key)
{
	t_list	*children;

	children = env_tree->childrens;
	while (children)
	{
		del_env_var(children->content, key);
		children = children->next;
	}
}

void	del_env_var(t_env_tree *env_tree, char *key)
{
	t_env_data	*prev;
	t_env_data	*env;
	t_env_data	*next;
	size_t		len;

	prev = NULL;
	env = env_tree->env;
	len = ft_strlen(key);
	while (env)
	{
		next = env->next;
		if (len == ft_strlen(env->key) && ft_strncmp(key, env->key, len))
		{
			if (prev)
				prev->next = next;
			else
				env_tree->env = next;
		}
		else
			prev = env;
		env = next;
	}
	del_env_var_childrens(env_tree, key);
}
