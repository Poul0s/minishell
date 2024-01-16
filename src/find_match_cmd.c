/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_match_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 22:59:51 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/16 03:11:31 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"
#include "libft.h" 
#include <stdlib.h>
#include <dirent.h>

void	find_match_from_dir(t_list **head, char *pwd, const char *start_cmd)
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
	(void)head;
	closedir(dir);
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
	//free_split();
	//lst_clear();
	(void)paths_cpy;
	return (head);
}
