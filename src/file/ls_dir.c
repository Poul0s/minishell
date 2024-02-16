/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 20:11:46 by psalame           #+#    #+#             */
/*   Updated: 2024/02/16 01:20:47 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "command_Int.h"

static DIR	*open_current_dir(void)
{
	char	*cwd;
	DIR		*res;

	cwd = return_pwd();
	if (!cwd)
		return (NULL);
	res = opendir(cwd);
	free(cwd);
	return (res);
}

t_list	*ls_dir(DIR **dir)
{
	t_list			*files;
	t_list			*node;
	struct dirent	*current_file;

	files = NULL;
	*dir = open_current_dir();
	if (!(*dir))
		return (NULL);
	current_file = readdir(*dir);
	while (current_file)
	{
		if (current_file->d_name[0] != '.')
		{
			node = ft_lstnew(current_file);
			if (!node)
				ft_lstclear(&files, NULL);
			if (!node)
				break ;
			ft_lstadd_back(&files, node);
		}
		current_file = readdir(*dir);
	}
	return (files);
}
