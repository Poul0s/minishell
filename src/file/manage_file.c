/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:05:32 by babonnet          #+#    #+#             */
/*   Updated: 2024/02/06 20:19:09 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"
#include "libft.h"
#include "command.h"
#include <errno.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>


void here_doc(char *delimiter, int fd)
{
	char *line_read;
	int	delimiter_len;

	if (!delimiter)
		return ;
	delimiter_len = ft_strlen(delimiter) + 1;
	while (1)
	{
		line_read = readline(">");
		if (*line_read && !ft_strncmp(line_read, delimiter, delimiter_len))
			break;
		if (fd != -1)
		{
			ft_putstr_fd(line_read, fd);
			write(fd, "\n", 1);
		}
	}
}

void manage_infile(t_list *infile, int fd)
{
	t_infile *infile_content;
	int fd_file;

	// manage fd redirection
	if (!infile)
	{
		dup2(fd, STDIN_FILENO);
		return ;
	}
	infile_content = infile->content;
	if (!infile_content)
		return ;
	fd_file = open(infile_content->filename, O_RDONLY);
	if (fd_file == -1)
	{
		ft_dprintf(2, "minishell : %s", strerror(errno));
		return ;
	}
	dup2(fd_file, STDIN_FILENO);
	close(fd_file);

}

void manage_outfile(t_list *outfiles, int fd)
{
	t_outfile *out;

	while(outfiles)
	{
		out = outfiles->content;
		if (out->append)
			fd = open(out->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		fd = open(out->filename, O_WRONLY | O_CREAT , 0644);
		outfiles = outfiles->next;
		if (outfiles->next)
			close(fd);
	}
	if (fd == STDOUT_FILENO)
		return ;
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
