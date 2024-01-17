/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:09:11 by psalame           #+#    #+#             */
/*   Updated: 2024/01/17 17:27:26 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_manager.h"

t_env_tree	*create_env_tree(t_env_tree *parent, char **env)
{
	t_env_tree	*env_tree_node;

	env_tree_node = malloc(sizeof(t_env_tree));
	if (!env_tree_node)
	{
		free(env_tree_node);
		return (NULL);
	}
	env_tree_node->childrens = NULL;
	env_tree_node->env = convert_strs_to_env_data(env);
	if (parent)
		add_env_tree_children(parent, env_tree_node);
	return (env_tree_node);
}
