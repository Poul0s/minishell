/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:01:28 by psalame           #+#    #+#             */
/*   Updated: 2024/01/15 20:14:46 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H
# include <stdbool.h>
# include "libft.h"

// files structures

typedef struct s_infile
{
	int		fd;
	char	*filename;
}	t_infile;

typedef struct s_outfile
{
	int		fd;
	bool	append;
	char	*filename;
}	t_outfile;

typedef struct s_heredoc
{
	int		fd;
	char	*delimiter;
}	t_heredoc;

// commands structures

typedef struct s_command
{
	char					*executable;
	char					**arguments;
	t_list					*infiles; // chained list of t_infile
	t_list					*outfiles; // chained list of t_outfile
	t_list					*here_documents; // chained list of t_heredoc
	struct s_command_line	*on_success;
	struct s_command_line	*on_error;
	
}	t_command;

typedef struct s_command_line
{
	t_command				*command;
	struct s_command_line	*pipe_next;
	struct s_command_line	*next;
}	t_command_line;

t_command_line	*parse_cmd_line(char *command_line);

#endif
