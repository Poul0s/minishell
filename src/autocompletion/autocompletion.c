/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:33:31 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/23 01:14:34 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocompletion.h"
#include <dirent.h>

void	pop(void *value)
{
	free(value);
}

char	*autocompletion(const char *str, int status)
{
	static t_list	*head = NULL;
	t_word			*word;

	if (!head)
	{
		word = wich_word();
		if (!word)
			return (NULL);
		//ft_printf("\n%s| %s|\n", word->path, word->word);
		if (!word->word && word->path && word->word[ft_strlen(word->path) - 1] != '/')	
			head = ft_lstnew(ft_strjoin(word->path , "/"));
		else if (is_first() && !word->path)
		{
			head = find_match_cmd(word->word);
			ft_lstadd_back(&head, find_match_file(word));
		}
		else
			head = find_match_file(word);
		free(word);
	}
	if (status)
		head = head->next;
	if (!head)
	{
		ft_lstclear(&head, pop);
		head = NULL;
		return (NULL);
	}
	return ((char *)head->content);
	(void)str;
}
