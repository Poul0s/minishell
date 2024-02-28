/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:33:31 by babonnet          #+#    #+#             */
/*   Updated: 2024/02/28 14:56:33 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocompletion.h"

static t_list	*create_word_list(t_word *word)
{
	t_list	*lst;

	lst = NULL;
	if (!word->word && word->path
		&& word->word[ft_strlen(word->path) - 1] != '/')
		lst = ft_lstnew(ft_strjoin(word->path, "/"));
	else if (is_first() && !word->path)
	{
		lst = find_match_cmd(word->word);
		ft_lstadd_back(&lst, find_match_file(word));
	}
	else
		lst = find_match_file(word);
	return (lst);
}

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
		lst = create_word_list(word);
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
