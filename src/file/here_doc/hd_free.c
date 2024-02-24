/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:35:31 by babonnet          #+#    #+#             */
/*   Updated: 2024/02/23 23:01:21 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include <unistd.h>

void	pop_infile(void *content)
{
	free(((t_infile *)content)->filename);
	free(((t_infile *)content)->delimiter);
	free(content);
}

void	close_here_doc(t_command *cmd)
{
	t_infile	*infile;

	if (!cmd->infiles)
		return ;
	infile = cmd->infiles->content;
	if (infile && infile->here_doc == true && infile->filename)
		unlink(infile->filename);
}

void	free_here_doc(t_command_group *cmd)
{
	if (cmd->command)
		close_here_doc(cmd->command);
	if (cmd->pipe_next)
		free_here_doc(cmd->pipe_next);
	if (cmd->on_success)
		free_here_doc(cmd->on_success);
	if (cmd->on_error)
		free_here_doc(cmd->on_error);
}
