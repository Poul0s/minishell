/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:18:15 by psalame           #+#    #+#             */
/*   Updated: 2024/01/18 14:06:25 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (list == NULL)
		return (list);
	list->content = content;
	list->next = NULL;
	return (list);
}

t_list	*ft_lstnew_fallback(void *content, void (*fallback)(void *data))
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (list == NULL)
	{
		(*fallback)(content);
		return (list);
	}
	list->content = content;
	list->next = NULL;
	return (list);
}
