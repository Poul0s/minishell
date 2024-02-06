/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:29:55 by babonnet          #+#    #+#             */
/*   Updated: 2024/02/06 20:09:59 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "here_doc.h"
#include <readline/readline.h>

void	read_here_doc(char *delimiter, int fd)
{
	char	*line_read;
	int		delimiter_len;

	if (!delimiter)
		return ;
	delimiter_len = ft_strlen(delimiter) + 1;
	while (1)
	{
		// access
		line_read = readline(">");
		if (!line_read || !ft_strncmp(line_read, delimiter, delimiter_len))
			break ;
		if (fd != -1)
		{
			ft_putstr_fd(line_read, fd);
			write(fd, "\n", 1);
		}
	}
}

void	generate_here_doc(t_list *infiles)
{
	t_list		*head;
	t_infile	*infile_content;
	char		*file;
	int			fd_file;

	fd_file = -1;
	head = infiles;
	while (infiles)
	{
		infile_content = infiles->content;
		if (infile_content->here_doc == true)
		{
			if (!infiles->next)
				file = create_tmp_file(&fd_file);
			read_here_doc(infile_content->delimiter, fd_file);
			if (!infiles->next)
				add_here_doc_data(&head, fd_file, file);
		}
		else if (!infiles->next)
			add_file_data(&head, infile_content->fd);
		infiles = infiles->next;
	}
	if (fd_file != -1)
		close(fd_file);
}

void	manage_here_doc(t_command_group *g_cmd)
{
	if (g_cmd->command)
		generate_here_doc(g_cmd->command->infiles);
	if (g_cmd->pipe_next)
		manage_here_doc(g_cmd->pipe_next);
	if (g_cmd->on_success)
		manage_here_doc(g_cmd->on_success);
	if (g_cmd->on_error)
		manage_here_doc(g_cmd->on_error);
}
