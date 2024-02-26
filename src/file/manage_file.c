/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:05:32 by babonnet          #+#    #+#             */
/*   Updated: 2024/02/26 21:27:20 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "ft_print.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <unistd.h>

void	here_doc(char *delimiter, int fd)
{
	char	*line_read;
	int		delimiter_len;

	if (!delimiter)
		return ;
	delimiter_len = ft_strlen(delimiter) + 1;
	while (1)
	{
		line_read = readline(">");
		if (*line_read && !ft_strncmp(line_read, delimiter, delimiter_len))
			break ;
		if (fd != -1)
		{
			ft_putstr_fd(line_read, fd);
			write(fd, "\n", 1);
		}
	}
}

int	manage_infile(t_list *infile, int fd)
{
	t_infile	*infile_content;

	if (!infile)
	{
		dup2(fd, STDIN_FILENO);
		return (0);
	}
	while (infile)
	{
		infile_content = infile->content;
		if (infile_content->here_doc == false
			&& access(infile_content->filename, R_OK) == -1)
		{
			ft_dprintf(2, "minishell: %s: No such file or directory\n",
				infile_content->filename);
			return (1);
		}
		infile = infile->next;
	}
	if (infile_content->here_doc == false)
		infile_content->fd = open(infile_content->filename, O_RDONLY);
	dup2(infile_content->fd, STDIN_FILENO);
	return (0);
}

int	manage_outfile(t_list *outfiles, int fd)
{
	t_outfile	*out;

	while (outfiles)
	{
		out = outfiles->content;
		if (out->append)
			fd = open(out->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(out->filename, O_WRONLY | O_CREAT, 0644);
		if (fd == -1)
		{
			ft_dprintf(2, "minishell: %s: Permission denied\n", out->filename);
			return (1);
		}
		if (outfiles->next)
			close(fd);
		outfiles = outfiles->next;
	}
	if (fd == STDOUT_FILENO)
		return (0);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}
