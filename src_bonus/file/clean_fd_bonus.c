/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_fd_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 18:25:18 by babonnet          #+#    #+#             */
/*   Updated: 2024/02/28 19:52:28 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_bonus.h"
#include "libft.h"

static void	close_last_fd(t_list *infile)
{
	t_infile	*infile_content;

	if (infile)
	{
		while (infile)
		{
			infile_content = infile->content;
			infile = infile->next;
		}
		if (infile_content->fd)
			close(infile_content->fd);
	}
}

void	close_all_fd(t_command_group *g_cmd)
{
	if (g_cmd->command)
		close_last_fd(g_cmd->command->infiles);
	if (g_cmd->pipe_next)
		close_all_fd(g_cmd->pipe_next);
	if (g_cmd->on_success)
		close_all_fd(g_cmd->on_success);
	if (g_cmd->on_error)
		close_all_fd(g_cmd->on_error);
}
