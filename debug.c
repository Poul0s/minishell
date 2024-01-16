/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 20:24:31 by psalame           #+#    #+#             */
/*   Updated: 2024/01/16 01:50:31 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_command_line(t_command_group *command, int depth);

static void print_heredoc(void *heredoc_data)
{
	t_heredoc	*heredoc = heredoc_data;
	ft_printf(" %d<< %s", heredoc->fd, heredoc->delimiter);
}

static void print_infile(void *infile_data)
{
	t_infile	*infile = infile_data;
	ft_printf(" %d< %s", infile->fd, infile->filename);
}

static void print_outfile(void *outfile_data)
{
	t_outfile	*outfile = outfile_data;
	ft_printf(" %d>", outfile->fd);
	if (outfile->append)
		ft_printf(">");
	ft_printf(" %s", outfile->filename);
}

static void	print_command(t_command *command, int depth)
{
	char	**arguments;

	ft_putchar_rep(' ', depth * 4, 1);
	ft_printf("%s", command->executable);
	arguments = command->arguments;
	while (*++arguments)
		ft_printf(" %s", *arguments);
	ft_lstiter(command->infiles, &print_infile);
	ft_lstiter(command->here_documents, &print_heredoc);
	ft_lstiter(command->outfiles, &print_outfile);
	ft_printf("\n%*c\n", depth * 4 + 1, '{');
	if (command->on_success)
	{
		ft_printf("\033[0;32m");
		print_command_line(command->on_success, depth + 1);
		ft_printf("\033[0m");
	}
	if (command->on_error)
	{
		ft_printf("\033[0;31m");
		print_command_line(command->on_error, depth + 1);
		ft_printf("\033[0m");
	}
	ft_printf("\n%*c\n", depth * 4 + 1, '}');
}

void	print_command_line(t_command_group *command, int depth)
{
	if (command)
	{
		print_command(command->command, depth);
		if (command->pipe_next)
			print_command_line(command->pipe_next, depth + 1);
	}
	else if (depth == 0)
		ft_printf("end\n");
}