/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion_dir_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:28:34 by babonnet          #+#    #+#             */
/*   Updated: 2024/02/28 19:46:30 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocompletion_bonus.h"
#include "libft.h"
#include <dirent.h>

void	add_file(t_list **head, struct dirent *dirent, t_word *word)
{
	char	*file;
	char	*join_file;

	if (word && word->path)
		join_file = ft_strjoin(word->path, dirent->d_name);
	else
		join_file = ft_strdup(dirent->d_name);
	if (dirent->d_type == DT_DIR)
	{
		file = ft_strjoin(join_file, "/");
		if (!file)
			return ;
		if (ft_lstadd_back(head, ft_lstnew(file)) == NULL)
			free(file);
	}
	else
	{
		file = ft_strdup(join_file);
		if (!file)
			return ;
		if (ft_lstadd_back(head, ft_lstnew(file)) == NULL)
			free(file);
	}
	free(join_file);
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
		add_file(&head, dirent, NULL);
		dirent = readdir(dir);
	}
	closedir(dir);
	return (head);
}
