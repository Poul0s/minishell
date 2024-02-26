/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:29:55 by babonnet          #+#    #+#             */
/*   Updated: 2024/02/26 20:00:28 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "ft_print.h"
#include "here_doc.h"
#include <readline/readline.h>

int	read_here_doc(char *delimiter, int fd, char *file_name)
{
	char	*line_read;
	int		delimiter_len;

	if (!delimiter)
		return (0);
	delimiter_len = ft_strlen(delimiter) + 1;
	while (1)
	{
		if (fd != -1 && access(file_name, W_OK) == -1)
		{
			ft_dprintf(2,
				"minishell: here_doc temporary file has ben deleted\n");
			return (1);
		}
		line_read = readline("> ");
		if (!line_read)
		{
			ft_dprintf(2, "minishell: warning: here-document ");
			ft_dprintf(2, "delimited by end-of-file (wanted `%s')\n",
				delimiter);
			break ;
		}
		if (!ft_strncmp(line_read, delimiter, delimiter_len))
			break ;
		if (fd != -1)
		{
			ft_putstr_fd(line_read, fd);
			write(fd, "\n", 1);
		}
	}
	return (0);
}

void	generate_here_doc(t_list *infiles, int *error)
{
	t_infile	*infile_content;
	char		*file;
	int			fd_file;

	fd_file = -1;
	while (infiles)
	{
		infile_content = infiles->content;
		if (infile_content->here_doc == true)
		{
			if (!infiles->next)
				file = create_tmp_file(&fd_file);
			*error += read_here_doc(infile_content->delimiter, fd_file, file);
			if (!infiles->next)
				add_here_doc_data(infiles->content, fd_file, file);
		}
		infiles = infiles->next;
	}
	if (fd_file != -1)
		close(fd_file);
}

void	manage_here_doc(t_command_group *g_cmd, int *error)
{
	if (g_cmd->command)
		generate_here_doc(g_cmd->command->infiles, error);
	if (g_cmd->pipe_next && !*error)
		manage_here_doc(g_cmd->pipe_next, error);
	if (g_cmd->on_success && !*error)
		manage_here_doc(g_cmd->on_success, error);
	if (g_cmd->on_error && !*error)
		manage_here_doc(g_cmd->on_error, error);
}
