/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env_tree_children.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:25:41 by psalame           #+#    #+#             */
/*   Updated: 2024/01/17 14:32:42 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_manager.h"

void	add_env_tree_children(t_env_tree *parent, t_env_tree *children)
{
	t_list	*node;

	node = ft_lstnew(children);
	if (!node)
		return ;
	ft_lstadd_back(&(parent->childrens), node);
}
