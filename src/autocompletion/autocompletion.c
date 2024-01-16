/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:33:31 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/16 18:56:26 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linkedList.h"
#include "ft_string.h"
#include "minishell.h"
#include <dirent.h>
#include <readline/readline.h>

void	pop(void *value)
{
	free(value);
}

char	*autocompletion(const char *str, int status)
{
	static t_list	*head = NULL;
	char			*word;

	if (!head)
	{
		word = wich_word();
		if (!word)
			return (NULL);
		if (rl_point == 0)
			head = autocompletion_dir(NULL);
		else
		{
			head = find_match_cmd(word);
			ft_lstadd_back(&head, find_match_file(word));
		}
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
