/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_redirection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 00:17:35 by psalame           #+#    #+#             */
/*   Updated: 2024/02/27 16:49:36 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_Int.h"

static void	parse_here_doc(t_string_index *command_line,
						t_command *cmd)
{
	char		*delimiter;
	t_infile	*heredoc_data;
	t_list		*node;

	command_line->i += 2;
	delimiter = parse_argument(command_line, NULL, NULL);
	heredoc_data = malloc(sizeof(t_infile));
	node = ft_lstnew(NULL);
	if (!delimiter || !heredoc_data || !node)
	{
		free(delimiter);
		free(heredoc_data);
		free(node);
		return ;
	}
	heredoc_data->here_doc = true;
	heredoc_data->delimiter = delimiter;
	node->content = heredoc_data;
	if (command_line->str[command_line->i] == 0)
		command_line->i--;
	ft_lstadd_back(&(cmd->infiles), node);
}

static void	parse_outfile(t_string_index *command_line,
						t_command *cmd)
{
	char		*filename;
	t_outfile	*outfile_data;
	t_list		*node;
	bool		append_mode;

	append_mode = command_line->str[command_line->i + 1] == '>';
	command_line->i += 1 + append_mode;
	filename = parse_argument(command_line, NULL, NULL);
	outfile_data = malloc(sizeof(t_outfile));
	node = ft_lstnew(NULL);
	if (!filename || !outfile_data || !node)
	{
		free(filename);
		free(outfile_data);
		free(node);
		return ;
	}
	outfile_data->append = append_mode;
	outfile_data->filename = filename;
	node->content = outfile_data;
	if (command_line->str[command_line->i] == 0)
		command_line->i--;
	ft_lstadd_back(&(cmd->outfiles), node);
}

static void	parse_infile(t_string_index *command_line,
						t_command *cmd)
{
	char		*filename;
	t_infile	*infile_data;
	t_list		*node;

	command_line->i += 1;
	filename = parse_argument(command_line, NULL, NULL);
	infile_data = malloc(sizeof(t_infile));
	node = ft_lstnew(NULL);
	if (!filename || !infile_data || !node)
	{
		free(filename);
		free(infile_data);
		free(node);
		return ;
	}
	infile_data->filename = filename;
	infile_data->here_doc = false;
	node->content = infile_data;
	if (command_line->str[command_line->i] == 0)
		command_line->i--;
	ft_lstadd_back(&(cmd->infiles), node);
}

void	parse_file_redirection(t_string_index *command_line, t_command *cmd)
{
	if (command_line->str[command_line->i] == '<')
	{
		if (command_line->str[command_line->i + 1] == '<')
			parse_here_doc(command_line, cmd);
		else
			parse_infile(command_line, cmd);
	}
	else
		parse_outfile(command_line, cmd);
}
