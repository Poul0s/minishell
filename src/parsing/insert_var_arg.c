/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_var_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:31:48 by psalame           #+#    #+#             */
/*   Updated: 2024/02/15 21:19:38 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "command_Int.h"
#include "libft.h"

static void	calculate_var_arg_pos(t_variable_argument *var_arg,
								char **current_arg,
								t_list **prev_arguments)
{
	var_arg->argument_index = ft_strlen(*current_arg);
	if (*current_arg == NULL)
		*current_arg = ft_strdup("");
	var_arg->argument_number = ft_lstsize(*prev_arguments);
}

t_list	*insert_var_arg(t_current_focus *foc,
						t_list **prev_arguments,
						char *argument_data,
						t_var_arg_type type)
{
	t_variable_argument	*var_arg;
	t_list				*node;

	var_arg = malloc(sizeof(t_variable_argument));
	if (!var_arg)
	{
		free(argument_data);
		return (NULL);
	}
	var_arg->type = type;
	var_arg->data = argument_data;
	var_arg->disable_multiple_args = foc->dblquote;
	calculate_var_arg_pos(var_arg, &(foc->data), prev_arguments);
	node = ft_lstnew(var_arg);
	if (!node)
	{
		free(argument_data);
		free(var_arg);
	}
	return (node);
}
