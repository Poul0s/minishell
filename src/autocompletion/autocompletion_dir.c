/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion_dir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:28:34 by babonnet          #+#    #+#             */
/*   Updated: 2024/02/27 23:43:54 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <dirent.h>

void	add_file(t_list **head, struct dirent *dirent)
{
	char	*file;

	if (dirent->d_type == DT_DIR)
	{
		file = ft_strjoin(dirent->d_name, "/");
		if (!file)
			return ;
		if (ft_lstadd_back(head, ft_lstnew(file)) == NULL)
			free(file);
	}
	else
	{
		file = ft_strdup(dirent->d_name);
		if (!file)
			return ;
		if (ft_lstadd_back(head, ft_lstnew(file)) == NULL)
			free(file);
	}
}

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
		add_file(&head, dirent);
		dirent = readdir(dir);
	}
	closedir(dir);
	return (head);
}
