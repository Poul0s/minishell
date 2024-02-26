/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:33:31 by babonnet          #+#    #+#             */
/*   Updated: 2024/02/24 18:52:57 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocompletion.h"

char	*autocompletion(const char *str, int status)
{
	static t_list	**head;
	static t_list	*lst;
	t_word			*word;

	if (!lst)
	{
		word = wich_word();
		if (!word)
			return (NULL);
		if (!word->word && word->path && word->word[ft_strlen(word->path) - 1] != '/')	
			lst = ft_lstnew(ft_strjoin(word->path , "/"));
		else if (is_first() && !word->path)
		{
			lst = find_match_cmd(word->word);
			ft_lstadd_back(&lst, find_match_file(word));
		}
		else
			lst = find_match_file(word);
		head = &lst;
		free(word);
	}
	if (status)
		lst = lst->next;
	if (!lst)
	{
		ft_lstclear(head, free);
		return (NULL);
	}
	return ((char *)lst->content);
	(void)str;
}
