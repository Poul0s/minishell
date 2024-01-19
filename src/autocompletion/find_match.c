/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_match.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 22:59:51 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/19 12:54:50 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "libft.h" 
#include "autocompletion.h" 
#include <stdlib.h>
#include <dirent.h>

static void	find_match_from_dir(t_list **head, char *pwd, const char *start_cmd)
{
	int		start_len;
	DIR		*dir;
	struct dirent  *dirent;

	if (!pwd || !start_cmd)
		return ;
	dir = opendir(pwd);
	if (!dir)
		return ;
	dirent = readdir(dir);
	start_len = ft_strlen(start_cmd);
	(void)start_len;
	while(dirent)
	{
		if (ft_strncmp(start_cmd, dirent->d_name, start_len) == 0)
			ft_lstadd_front(head, ft_lstnew(ft_strdup(dirent->d_name)));
		dirent = readdir(dir);
	}
	closedir(dir);
}

static void	free_split(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i])
	{
		if (strs[i])
			free(strs[i]);
		i++;
	}
	free(strs);
}

t_list *find_match_cmd(const char *start_cmd)
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
	while(*paths)
	{
		find_match_from_dir(&head, *paths, start_cmd);
		paths++;
	}
	free_split(paths_cpy);
	return (head);
}

static int is_all_path(const char *str)
{
	while (*str)
	{
		if (ft_strchr("./", *str))
			return (0);
		str++;
	}
	return (1);
}

t_list *find_match_file(t_word *word)
{
	t_list			*head;
	char			*dir_path_str;
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
		{
			if (word->path && !is_all_path(word->path))
				dir_path_str = ft_strjoin(word->path, dirent->d_name);
			else
				dir_path_str = dirent->d_name;
			if (dir_path_str && dirent->d_type == DT_DIR)
				ft_lstadd_back(&head, ft_lstnew(ft_strjoin(dir_path_str, "/")));
			else if (dir_path_str)
				ft_lstadd_back(&head, ft_lstnew(ft_strdup(dir_path_str)));
		}
		dirent = readdir(dir);
	}
	closedir(dir);
	return (head);
}

t_list *find_match_file1(t_word *word)
{
	t_list *head;
	DIR		*dir;
	struct dirent *dirent;
	char   *full_dname;
	char	*full_path;

	head = NULL;
	if (!word->path)
		word->path = ft_strdup("./");
	full_path = ft_strjoin(word->path, word->word);
	if (!word->path || !full_path)	
	{
		if (full_path)
			free(full_path);
		return (NULL);
	}
	dir = opendir(word->path);
	if (!dir)
		return (NULL);
	dirent = readdir(dir);
	while(dirent)
	{
		full_dname = ft_strjoin(word->path, dirent->d_name);
		if (full_dname)
		{
			ft_printf("\n%s    %s", full_path,  full_dname);
			if (ft_strncmp(full_path, full_dname, ft_strlen(word->word)) == 0)
			{
				if (dirent->d_type == DT_DIR)
					ft_lstadd_back(&head, ft_lstnew(ft_strjoin(full_dname, "/")));
				else if (full_dname)
					ft_lstadd_back(&head, ft_lstnew(ft_strdup(full_dname)));
			}
			dirent = readdir(dir);
			free(full_dname);
		}
	}
	closedir(dir);
	free(full_path);
	return (head);
}
