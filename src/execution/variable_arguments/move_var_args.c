/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_var_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:56:21 by psalame           #+#    #+#             */
/*   Updated: 2024/02/16 13:09:47 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

void	move_variable_arguments_index(t_list *variable_arguments,
										char *var_arg_str)
{
	size_t				var_arg_len;
	t_variable_argument	*var_arg;
	t_variable_argument	*current_var_arg;

	var_arg_len = ft_strlen(var_arg_str);
	var_arg = variable_arguments->content;
	variable_arguments = variable_arguments->next;
	while (variable_arguments)
	{
		current_var_arg = variable_arguments->content;
		if (current_var_arg->arg_nb == var_arg->arg_nb)
		{
			if (current_var_arg->arg_idx >= var_arg->arg_idx)
				current_var_arg->arg_idx += var_arg_len;
		}
		variable_arguments = variable_arguments->next;
	}
}

void	move_variable_arguments_number(t_list *var_args)
{
	size_t				min_index;
	t_variable_argument	*var_arg_data;

	var_arg_data = var_args->content;
	min_index = var_arg_data->arg_nb;
	while (var_args)
	{
		var_arg_data = var_args->content;
		if (var_arg_data->arg_nb > min_index)
			var_arg_data->arg_nb++;
		var_args = var_args->next;
	}
}
