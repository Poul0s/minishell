/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:33:31 by babonnet          #+#    #+#             */
/*   Updated: 2024/02/27 23:17:11 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocompletion.h"

char	*autocompletion(const char *str, int status)
{
	static t_list	*head;
	static t_list	*lst;
	t_word			*word;

	if (!lst)
	{
		word = wich_word();
		if (!word)
			return (NULL);
		if (!word->word && word->path && word->word[ft_strlen(word->path)
			- 1] != '/')
			lst = ft_lstnew(ft_strjoin(word->path, "/"));
		else if (is_first() && !word->path)
		{
			lst = find_match_cmd(word->word);
			ft_lstadd_back(&lst, find_match_file(word));
		}
		else
			lst = find_match_file(word);
		head = lst;
		free(word->word);
		free(word->path);
		free(word);
	}
	if (status)
		lst = lst->next;
	if (!lst)
	{
		ft_lstclear(&head, &free);
		return (NULL);
	}
	return ((char *)ft_strdup(lst->content));
	(void)str;
}
