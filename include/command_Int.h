/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_Int.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:41:32 by psalame           #+#    #+#             */
/*   Updated: 2024/01/17 13:32:01 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_INT_H
# define COMMAND_INT_H
# include "command.h"
# include "libft.h"

typedef struct s_current_focus
{
	bool	command_name;
	bool	quote;
	bool	dbl_quote;
	bool	parenthesis;
}	t_current_focus;

typedef struct s_string_index
{
	char	*str;
	size_t	i;
}	t_string_index;

void			str_i_skip_spaces(t_string_index *command_line);
char			*parse_argument(t_string_index *command_line, t_command *cmd, t_list **prev_arguments);
void			parse_command(t_string_index *command_line, t_command *command);
t_command		*parse_commands(t_string_index *command_line, char **env);
t_command_group	*parse_command_grp(t_string_index *command_line, char **env);
void			parse_file_redirection(t_string_index *command_line, char **argument, t_command *cmd);

#endif