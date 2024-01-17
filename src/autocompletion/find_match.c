/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_match.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 22:59:51 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/17 16:36:16 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 
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

t_list *find_match_file(const char *start_cmd)
{
	t_list			*head;
	DIR				*dir;
	struct dirent	*dirent;

	head = NULL;
	dir = opendir(".");
	if (!dir)
		return (NULL);
	dirent = readdir(dir);
	dirent = readdir(dir);
	dirent = readdir(dir);
	while (dirent)
	{
		if (ft_strncmp(start_cmd, dirent->d_name, ft_strlen(start_cmd)) == 0)
		{
			if (dirent->d_type == DT_DIR)
				ft_lstadd_back(&head, ft_lstnew(ft_strjoin(dirent->d_name, "/")));
			else
				ft_lstadd_back(&head, ft_lstnew(ft_strdup(dirent->d_name)));
		}
		dirent = readdir(dir);
	}
	closedir(dir);
	return (head);
}
