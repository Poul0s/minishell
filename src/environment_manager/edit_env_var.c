/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_env_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:29:29 by psalame           #+#    #+#             */
/*   Updated: 2024/01/17 17:28:51 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_manager.h"

static void	add_env_data_var(t_env_data **env_data, char *key, char *value)
{
	t_env_data	*last_node;
	t_env_data	*new_node;
	
	if (!env_data)
		return ;
	new_node = malloc(sizeof(t_env_data));
	if (!new_node)
	{
		free(value);
		return ;
	}
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	if (*env_data == NULL)
		*env_data = new_node;
	else
	{
		last_node = *env_data;
		while (last_node->next)
			last_node = last_node->next;
		last_node->next = new_node;
	}
}

void	edit_env_var(t_env_tree *env_tree, char *key, char *data)
{
	t_env_data	*env_res_object;
	t_list		*children;
	
	env_res_object = get_env_data(env_tree->env, key);
	if (!env_res_object)
		add_env_data_var(&(env_tree->env), key, data);
	else
		env_res_object->value = data;
	children = env_tree->childrens;
	while (children)
	{
		edit_env_var(children->content, key, data);
		children = children->next;
	}
}
