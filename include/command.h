/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:01:28 by psalame           #+#    #+#             */
/*   Updated: 2024/01/22 16:21:59 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H
# include <stdbool.h>
# include "libft.h"
# include "environment_manager.h"

// argument variables

typedef enum e_variable_argument_types
{
	WILDCARD,
	ENVIRONMENT_VARIABLE
}	t_variable_argument_type;

typedef struct s_variable_argument
{
	size_t						argument_number;
	size_t						argument_index;

	char						*data;
	t_variable_argument_type	type;
}	t_variable_argument;

// files structures

typedef struct s_infile
{
	int		fd;
	char	*filename;
}	t_infile;

typedef struct s_outfile
{
	int		fd; // if fd == -1 : write all outputs
	char	*filename;
	bool	append;
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
	t_list					*infiles;
	t_list					*outfiles; // if multime outfile has same fd -> write only on last file but create both files
	t_list					*here_documents;
	t_list					*argument_variables;
}	t_command;

typedef struct s_command_group
{
	t_env_tree				*env;
	t_command				*command;
	struct s_command_group	*on_success;
	struct s_command_group	*on_error;
	struct s_command_group	*pipe_next;
}	t_command_group;

t_command_group	*parse_cmd_line(char *command_line, t_env_tree *env);

#endif
