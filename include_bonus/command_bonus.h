/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:01:28 by psalame           #+#    #+#             */
/*   Updated: 2024/02/28 19:34:16 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_BONUS_H
# define COMMAND_BONUS_H
# include <stdbool.h>
# include "libft.h"
# include "environment_manager_bonus.h"

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
	ENV_VAR
}	t_var_arg_type;

typedef struct s_variable_argument
{
	size_t						arg_nb;
	size_t						arg_idx;
	bool						disable_multiple_args;

	char						*data;
	t_var_arg_type				type;
}	t_variable_argument;

// files structures

typedef struct s_infile
{
	int		fd;
	char	*filename;

	bool	here_doc;
	char	*delimiter;
}	t_infile;

typedef struct s_outfile
{
	int		fd;
	char	*filename;
	bool	append;
}	t_outfile;

// commands structures

typedef struct s_command
{
	char					**arguments;
	t_list					*infiles;
	t_list					*outfiles;
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
}	t_command_group;

t_command_group	*parse_cmd_line(char *command_line, char ***env);
char			**ft_strs_insert_str(char **src, char *new_elem, size_t pos);

#endif
