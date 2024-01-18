/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_Int.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:41:32 by psalame           #+#    #+#             */
/*   Updated: 2024/01/18 14:22:34 by psalame          ###   ########.fr       */
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
	bool	dblquote;
	bool	parenthesis;
}	t_current_focus;

typedef struct s_string_index
{
	char	*str;
	size_t	i;
}	t_string_index;

void			str_i_skip_spaces(t_string_index *command_line);
char			*parse_argument(t_string_index *command_line, t_command *cmd, t_list **prev_arguments, t_env_tree *env);
t_command		*parse_command(t_string_index *command_line, t_env_tree *env);
t_command_group	*parse_command_grp(t_string_index *command_line, t_env_tree *env);
void			parse_file_redirection(t_string_index *command_line, char **argument, t_command *cmd, t_env_tree *env);

#endif