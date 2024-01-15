/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:01:28 by psalame           #+#    #+#             */
/*   Updated: 2024/01/15 16:35:52 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H
# include <stdbool.h>

typedef struct s_current_focus
{
	bool	command_name;
	bool	quote;
	bool	dbl_quote;
	bool	env_var;
}	t_current_focus;

typedef struct s_command
{
	char	*executable;
	char	**arguments;
	
	struct s_command	*pipe_next;
}	t_command;

typedef struct s_command_group
{
	struct s_command		*commands;
	struct s_command_group	*on_success;
	struct s_command_group	*on_error;
}	t_command_group;

typedef struct s_command_line
{
	t_command_group			*command_group;
	struct s_command_line	*next;
}	t_command_line;

#endif
