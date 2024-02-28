/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_match_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 22:59:51 by babonnet          #+#    #+#             */
/*   Updated: 2024/02/28 19:46:30 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocompletion_bonus.h"
#include "ft_string.h"
#include "libft.h"
#include <dirent.h>
#include <stdlib.h>

static void	find_match_from_dir(t_list **head, char *pwd, const char *start_cmd)
{
	int				start_len;
	DIR				*dir;
	struct dirent	*dirent;

	if (!pwd || !start_cmd)
		return ;
	dir = opendir(pwd);
	if (!dir)
		return ;
	dirent = readdir(dir);
	start_len = ft_strlen(start_cmd);
	(void)start_len;
	while (dirent)
	{
		if (ft_strncmp(start_cmd, dirent->d_name, start_len) == 0)
			add_file(head, dirent, NULL);
		dirent = readdir(dir);
	}
	closedir(dir);
}

t_list	*find_match_cmd(const char *start_cmd)
{
	char	*env;
	char	**paths;
	char	**paths_cpy;
	t_list	*head;

	head = NULL;
	env = getenv("PATH");
	paths = ft_split(env, ':');
	if (!paths)
		return (NULL);
	paths_cpy = paths;
	while (*paths)
	{
		find_match_from_dir(&head, *paths, start_cmd);
		paths++;
	}
	ft_free_strs(paths_cpy);
	return (head);
}

t_list	*find_match_file(t_word *word)
{
	t_list			*head;
	DIR				*dir;
	struct dirent	*dirent;

	head = NULL;
	if (word->path)
		dir = opendir(word->path);
	else
		dir = opendir(".");
	if (!dir)
		return (NULL);
	dirent = readdir(dir);
	dirent = readdir(dir);
	dirent = readdir(dir);
	while (dirent)
	{
		if (ft_strncmp(word->word, dirent->d_name, ft_strlen(word->word)) == 0)
			add_file(&head, dirent, word);
		dirent = readdir(dir);
	}
	closedir(dir);
	return (head);
}
