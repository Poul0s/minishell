/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_Int.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:41:32 by psalame           #+#    #+#             */
/*   Updated: 2024/02/26 13:53:03 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_INT_H
# define COMMAND_INT_H
# include "command.h"
# include "libft.h"
# include "string_index.h"
# include <sys/types.h>
# include <dirent.h>
# define SORT_TABLE "!\"#%&'()*+,-:;<=>?@[\\]^_`{|}~$0123456789aAbBcCdDeEfFgGh\
HiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ"

typedef struct s_current_focus
{
	bool	command_name;
	bool	quote;
	bool	dblquote;
	bool	parenthesis;
	char	*data;
}	t_current_focus;

t_list			*insert_var_arg(t_current_focus *foc,
					t_list **prev_arguments,
					char *argument_data,
					t_var_arg_type type);

char			*parse_argument(t_string_index *command_line,
					t_command *cmd,
					t_list **prev_arguments);

t_command		*parse_command(t_string_index *command_line, char ***env);

t_command_group	*parse_command_grp(t_string_index *command_line, char ***env);
void			parse_command_grp_operators(t_command_group *grp,
					t_string_index *command_line,
					char ***env);

void			parse_file_redirection(t_string_index *command_line,
					char **argument,
					t_command *cmd);

bool			is_var_arg_char_correct(t_string_index *cmd_line,
										int start,
										int current)

void			convert_variable_arguments(t_command *command);
void			manage_wildcard(t_list *variable_arguments,
					t_command *command);
void			sort_files(t_list *files);
t_list			*ls_dir(DIR **dir);

#endif