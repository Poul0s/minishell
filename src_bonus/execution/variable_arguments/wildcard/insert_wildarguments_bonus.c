/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_wildarguments.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:59:47 by psalame           #+#    #+#             */
/*   Updated: 2024/02/28 19:37:38 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "command_Int_bonus.h"
#include "../variable_arguments_Int_bonus.h"

static bool	is_folder_only(t_command *cmd, t_list *var_args)
{
	t_variable_argument	*var_arg_data;
	char				*argument;

	var_arg_data = var_args->content;
	argument = cmd->arguments[var_arg_data->arg_nb];
	return (argument[ft_strlen(argument) - 1] == '/');
}

static void	insert_arg(struct dirent *file,
						t_command *cmd,
						size_t *i,
						t_list *var_args)
{
	char				**new_args;
	char				*new_arg;
	bool				folder_only;

	folder_only = is_folder_only(cmd, var_args);
	new_arg = ft_strdup(file->d_name);
	if (new_arg && folder_only)
		new_arg = ft_strfjoin_chr(new_arg, '/');
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
	bool				folder_only;

	var_arg_data = var_args->content;
	folder_only = is_folder_only(cmd, var_args);
	file = files->content;
	new_arg = ft_strdup(file->d_name);
	if (new_arg && folder_only)
		new_arg = ft_strfjoin_chr(new_arg, '/');
	if (new_arg)
	{
		free(cmd->arguments[var_arg_data->arg_nb]);
		cmd->arguments[var_arg_data->arg_nb] = new_arg;
	}
	i = var_arg_data->arg_nb + 1;
	while (files->next)
	{
		file = files->next->content;
		insert_arg(file, cmd, &i, var_args);
		files = files->next;
	}
}
