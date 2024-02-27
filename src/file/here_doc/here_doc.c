/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:29:55 by babonnet          #+#    #+#             */
/*   Updated: 2024/02/27 13:59:58 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "ft_print.h"
#include "here_doc.h"
#include <readline/readline.h>

void	generate_here_doc(t_list *infiles,
						int *error,
						t_execution_data exec_data)
{
	t_infile	*infile_content;
	char		*file;
	int			fd_file;

	fd_file = -1;
	file = NULL;
	while (infiles)
	{
		infile_content = infiles->content;
		if (infile_content->here_doc == true)
		{
			if (!infiles->next)
				file = create_tmp_file(&fd_file);
			*error += read_here_doc(infile_content->delimiter,
					fd_file,
					file,
					exec_data);
			if (!infiles->next)
				add_here_doc_data(infiles->content, fd_file, file);
		}
		infiles = infiles->next;
	}
	if (fd_file != -1)
		close(fd_file);
}

void	manage_here_doc(t_command_group *g_cmd,
					int *error,
					t_execution_data exec_data)
{
	if (g_cmd->command)
		generate_here_doc(g_cmd->command->infiles, error, exec_data);
	if (g_cmd->pipe_next && !*error)
		manage_here_doc(g_cmd->pipe_next, error, exec_data);
	if (g_cmd->on_success && !*error)
		manage_here_doc(g_cmd->on_success, error, exec_data);
	if (g_cmd->on_error && !*error)
		manage_here_doc(g_cmd->on_error, error, exec_data);
}
