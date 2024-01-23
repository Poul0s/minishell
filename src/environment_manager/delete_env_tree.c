/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_env_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:07:28 by psalame           #+#    #+#             */
/*   Updated: 2024/01/23 18:44:41 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_manager.h"

static void	delete_env_data(t_env_data *data)
{
	t_env_data	*tmp;

	while (data)
	{
		tmp = data;
		data = data->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

void	delete_env_tree_childrens(t_env_tree *env)
{
	t_list	*node;

	while (env->childrens)
	{
		node = env->childrens;
		delete_env_tree(node->content);
		env->childrens = env->childrens->next;
	}
}

void	delete_env_tree(t_env_tree *env)
{
	delete_env_tree_childrens(env);
	delete_env_data(env->env);
	free(env);
}
