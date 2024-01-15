/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:01:28 by psalame           #+#    #+#             */
/*   Updated: 2024/01/15 14:17:01 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

typedef struct s_command
{
	char	*executable;
	char	**arguments;
	struct s_command	*pipe_next;
}	t_command;

typedef struct s_command_group
{
	struct s_command		*first;
	struct s_command_group	*on_success;
	struct s_command_group	*on_error;
}	t_command_group;

typedef struct s_command_line
{
	t_command_group	*commands_groups;
}	t_command_line;

#endif
