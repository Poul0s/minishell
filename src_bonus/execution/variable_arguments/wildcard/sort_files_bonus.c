/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:27:35 by psalame           #+#    #+#             */
/*   Updated: 2024/02/28 19:37:38 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "command_Int_bonus.h"

static int	chrcmp_ordered(char a, char b)
{
	const char	*sort_table = SORT_TABLE;
	long		posa;
	long		posb;

	posa = (long)ft_strchr(sort_table, a);
	posb = (long)ft_strchr(sort_table, b);
	if (!posa || !posb)
		return (a - b);
	posa = posa - ((long)sort_table);
	posb = posb - ((long)sort_table);
	return ((int)(posa - posb));
}

static int	comp_files(struct dirent *file_a, struct dirent *file_b)
{
	char	*s1;
	char	*s2;
	size_t	i;

	i = 0;
	s1 = file_a->d_name;
	s2 = file_b->d_name;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (chrcmp_ordered(s1[i], s2[i]));
		i++;
	}
	return (chrcmp_ordered(s1[i], s2[i]));
}

void	sort_files(t_list *files)
{
	void	*tmp;
	t_list	*sorting_file;
	t_list	*cursor_file;

	sorting_file = files;
	while (sorting_file && sorting_file->next)
	{
		cursor_file = sorting_file->next;
		while (cursor_file)
		{
			if (comp_files(sorting_file->content, cursor_file->content) > 0)
			{
				tmp = sorting_file->content;
				sorting_file->content = cursor_file->content;
				cursor_file->content = tmp;
			}
			cursor_file = cursor_file->next;
		}
		sorting_file = sorting_file->next;
	}
}
