/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_wildarguments.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:59:47 by psalame           #+#    #+#             */
/*   Updated: 2024/02/16 14:06:42 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "command_Int.h"
#include "../variable_arguments_Int.h"

static void	insert_arg(struct dirent *file,
						t_command *cmd,
						size_t *i,
						t_list *var_args)
{
	char				**new_args;
	char				*new_arg;

	new_arg = ft_strdup(file->d_name);
	if (new_arg)
	{
		new_args = ft_strs_insert_str(cmd->arguments, new_arg, *i);
		*i += 1;
		if (new_args)
		{
			free(cmd->arguments);
			cmd->arguments = new_args;
			move_variable_arguments_number(var_args);
		}
		else
			free(new_arg);
	}
}

void	insert_wildarguments(t_list *var_args, t_list *files, t_command *cmd)
{
	char				*new_arg;
	struct dirent		*file;
	size_t				i;
	t_variable_argument	*var_arg_data;

	file = files->content;
	new_arg = ft_strdup(file->d_name);
	var_arg_data = var_args->content;
	i = var_arg_data->arg_nb + 1;
	if (new_arg)
	{
		free(cmd->arguments[var_arg_data->arg_nb]);
		cmd->arguments[var_arg_data->arg_nb] = new_arg;
	}
	while (files->next)
	{
		file = files->next->content;
		insert_arg(file, cmd, &i, var_args);
		files = files->next;
	}
}
