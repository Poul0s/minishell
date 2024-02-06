/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 20:04:06 by babonnet          #+#    #+#             */
/*   Updated: 2024/02/01 17:19:58 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "command.h"
#include "execution.h"
#include <dirent.h>

int ft_wildcard(t_command *cmd, t_variable_argument *wc_data) // need to add offset for multiple wildcard
{
	DIR *dir;
	int index;
	int first;
	struct dirent *dirent;

	if (!wc_data)
		return (0);
	dir = opendir(".");
	if (!dir)
		return (1);
	dirent = readdir(dir);
	index = wc_data->argument_number;
	first = true;
	while (dirent)
	{
		if (dirent->d_name[0] != '.')
		{
			if (first)
			{
				free(cmd->arguments[index]);
				cmd->arguments[index] = ft_strdup(dirent->d_name);
				first = false;
				index++;
			}
			else
			{
				ft_strs_insert_str(cmd->arguments, ft_strdup(dirent->d_name), index);
				index++;
			}
		}
		dirent = readdir(dir);
	}
	return (ft_wildcard(cmd, wc_data->)
}
