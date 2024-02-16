/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_wildcard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:08:27 by psalame           #+#    #+#             */
/*   Updated: 2024/02/16 14:08:50 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "command_Int.h"
#include "../variable_arguments_Int.h"

ssize_t	get_next_wildcard(t_list **var_args)
{
	t_variable_argument	*var_arg_data;
	size_t				arg_number;
	ssize_t				res;

	res = -1;
	if (var_args && *var_args)
	{
		arg_number = ((t_variable_argument *)(*var_args)->content)->arg_nb;
		while (*var_args)
		{
			var_arg_data = (*var_args)->content;
			if (res == -1)
			{
				if (var_arg_data->arg_nb == arg_number)
					res = var_arg_data->arg_idx;
				*var_args = (*var_args)->next;
			}
			else if (var_arg_data->arg_nb != arg_number)
				*var_args = (*var_args)->next;
			else
				break ;
		}
	}
	return (res);
}
