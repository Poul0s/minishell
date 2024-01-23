/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_tree_children.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:53:43 by psalame           #+#    #+#             */
/*   Updated: 2024/01/23 18:42:11 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_manager.h"

t_env_tree	*create_env_tree_children(t_env_tree *parent)
{
	t_env_data	*parent_env_data;
	t_env_tree	*res;

	if (!parent)
		return (NULL);
	res = malloc(sizeof(t_env_tree));
	if (!res)
		return (NULL);
	res->env = NULL;
	res->childrens = NULL;
	add_env_tree_children(parent, res);
	parent_env_data = parent->env;
	while (parent_env_data)
	{
		edit_env_var(res, parent_env_data->key, parent_env_data->value);
		parent_env_data = parent_env_data->next;
	}
	return (res);
}
