/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion_dir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:28:34 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/25 00:07:29 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <dirent.h>

t_list	*autocompletion_dir(const char *path)
{
	t_list			*head;
	DIR				*dir;
	struct dirent	*dirent;

	head = NULL;
	if (!path)
		dir = opendir(".");
	else
		dir = opendir(path);
	if (!dir)
		return (NULL);
	dirent = readdir(dir);
	dirent = readdir(dir);
	dirent = readdir(dir);
	while (dirent)
	{
		if (dirent->d_type == DT_DIR)
			ft_lstadd_back(&head, ft_lstnew(ft_strjoin(dirent->d_name, "/")));
		else
			ft_lstadd_back(&head, ft_lstnew(ft_strdup(dirent->d_name)));
		dirent = readdir(dir);
	}
	closedir(dir);
	return (head);
}
