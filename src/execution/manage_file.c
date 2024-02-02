/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:05:32 by babonnet          #+#    #+#             */
/*   Updated: 2024/02/03 00:28:09 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "command.h"
#include <errno.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

static char	*create_tmp_file(int *fd)
{
	char	*file;
	int		fd_random;

	fd_random = open("/dev/random", O_RDONLY);
	if (fd_random == -1)
		return (NULL);
	file = ft_calloc(20, sizeof(char));
	if (!file)
	{
		close(fd_random);
		return (NULL);
	}
	while (1)
	{
		if (read(fd_random, file, 20) == -1)
			return (NULL);
		file[0] = '.';
		file[19] = '\0';
		*fd = open(file, O_CREAT | O_EXCL | O_WRONLY, 0644);
		if (*fd != -1)
		{
			close(fd_random);
			return (file);
		}
	}
}

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
	char *file;
	int fd_file;

	// manage fd redirection
	if (!infile)
		dup2(fd, STDIN_FILENO);
	else
	{
		fd_file = -1;
		while(infile)
		{
			infile_content = infile->content;
			if (infile_content->here_doc == true)
			{
				if (!infile->next)
					file = create_tmp_file(&fd_file);
				here_doc(infile_content->delimiter, fd_file);
				if (!infile->next)
				{
					close(fd_file);
					fd = open(file, O_RDONLY);
					dup2(fd, STDIN_FILENO);
					unlink(file);
					free(file);
				}
			}
			else if (!infile->next)
			{
				fd_file = open(infile_content->filename, O_RDONLY);
				if (fd_file < 0)
				{
					perror("oui");
					return ;
					// need to change
				}
				dup2(fd_file, STDIN_FILENO);
			}
			infile = infile->next;
		}
	}
}

void manage_outfile(t_list *outfiles, int fd)
{
	t_outfile *out;

	if (fd == STDOUT_FILENO)
		return ;
	while(outfiles)
	{
		close(fd);
		out = outfiles->content;
		if (out->append)
			fd = open(out->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		fd = open(out->filename, O_WRONLY | O_CREAT , 0644);
		outfiles = outfiles->next;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
