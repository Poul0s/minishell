/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_arguments_Int_bonus.h                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:55:51 by psalame           #+#    #+#             */
/*   Updated: 2024/02/28 19:55:29 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLE_ARGUMENTS_INT_BONUS_H
# define VARIABLE_ARGUMENTS_INT_BONUS_H

# include "command_bonus.h"
# include "libft.h"
# include <unistd.h>

void	move_variable_arguments_index(t_list *variable_arguments,
			char *var_arg_str);
void	move_variable_arguments_number(t_list *var_args);
void	insert_wildarguments(t_list *var_args, t_list *files, t_command *cmd);
ssize_t	get_next_wildcard(t_list **var_args);

#endif
