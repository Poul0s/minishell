/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:40:01 by psalame           #+#    #+#             */
/*   Updated: 2024/01/17 13:46:16 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstadd_back(t_list **lst, t_list *new)
{
	if (lst == NULL || new == NULL)
		return (NULL);
	if (*lst == NULL)
		*lst = new;
	else
		ft_lstlast(*lst)->next = new;
	return (new);
}
