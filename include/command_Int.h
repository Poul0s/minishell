/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_Int.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:41:32 by psalame           #+#    #+#             */
/*   Updated: 2024/01/20 15:52:30 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_INT_H
# define COMMAND_INT_H
# include "command.h"
# include "libft.h"
# include "string_index.h"

typedef struct s_current_focus
{
	bool	command_name;
	bool	quote;
	bool	dblquote;
	bool	parenthesis;
}	t_current_focus;
char			*parse_argument(t_string_index *command_line, t_command *cmd, t_list **prev_arguments, t_env_tree *env);
t_command		*parse_command(t_string_index *command_line, t_env_tree *env);
t_command_group	*parse_command_grp(t_string_index *command_line, t_env_tree *env);
void			parse_file_redirection(t_string_index *command_line, char **argument, t_command *cmd, t_env_tree *env);

#endif