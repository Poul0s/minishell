/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:01:28 by psalame           #+#    #+#             */
/*   Updated: 2024/01/29 15:32:51 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H
# include <stdbool.h>
# include "libft.h"
# include "environment_manager.h"

struct	s_command_group;
struct	s_sh_data;
typedef struct s_execution_data
{
	struct s_command_group	*base_command_line;
	struct s_sh_data		*shell_data;
	int						*pid;
	bool					forked;
}	t_execution_data;

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
	bool						disable_multiple_args;

	char						*data;
	t_variable_argument_type	type;
}	t_variable_argument; // todo add support for infile outfile && heredoc

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
	char					**arguments;
	t_list					*infiles;
	t_list					*outfiles; // if multime outfile has same fd -> write only on last file but create both files
	t_list					*here_documents;
	t_list					*argument_variables;
	char					***env;

	char					*executable;
	bool					last_pipe_cmd;
	t_execution_data		exec_data;
}	t_command;

typedef struct s_command_group
{
	t_command				*command;
	struct s_command_group	*on_success;
	struct s_command_group	*on_error;
	struct s_command_group	*pipe_next;

	bool					is_in_parenthesis; // todo check if and how to implement
}	t_command_group;

t_command_group	*parse_cmd_line(char *command_line, char ***env);
char			**ft_strs_insert_str(char **src, char *new_elem, size_t pos);

#endif
