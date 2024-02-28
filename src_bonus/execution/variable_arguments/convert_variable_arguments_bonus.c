/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_variable_arguments.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 21:25:10 by psalame           #+#    #+#             */
/*   Updated: 2024/02/28 19:37:38 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "command_Int_bonus.h"
#include "variable_arguments_Int_bonus.h"

extern int	g_exit_status;

static void	insert_argument(t_list *var_args,
							t_command *cmd,
							char *arg)
{
	t_variable_argument	*var_arg_data;
	char				**new_argument_list;
	size_t				insert_pos;

	var_arg_data = var_args->content;
	insert_pos = var_arg_data->arg_nb;
	while (var_args)
	{
		var_arg_data = var_args->content;
		if (var_arg_data->arg_nb >= insert_pos)
			var_arg_data->arg_nb++;
		var_args = var_args->next;
	}
	new_argument_list = ft_strs_insert_str(cmd->arguments, arg, insert_pos);
	if (new_argument_list)
	{
		free(cmd->arguments);
		cmd->arguments = new_argument_list;
	}
	else
	{
		free(new_argument_list);
		free(arg);
	}
}

static char	*insert_variable_data(t_list *variable_argument, t_command *cmd)
{
	t_variable_argument	*var_arg_data;
	char				**strs;
	char				*res;
	size_t				i;

	var_arg_data = variable_argument->content;
	if (var_arg_data->disable_multiple_args)
		res = ft_strdup(get_env_var(*(cmd->env), var_arg_data->data));
	else
	{
		strs = ft_split(get_env_var(*(cmd->env), var_arg_data->data), ' ');
		if (!strs || strs[0] == NULL)
		{
			free(strs);
			return (NULL);
		}
		i = 0;
		while (strs[i] && strs[i + 1])
			insert_argument(variable_argument, cmd, strs[i++]);
		res = strs[i];
		free(strs);
	}
	return (res);
}

static void	convert_env_var(t_list *var_arg, t_command *cmd)
{
	t_variable_argument	*va_data;
	char				*va_str;
	char				*new_arg;

	while (var_arg)
	{
		va_data = var_arg->content;
		if (va_data->type == ENV_VAR)
		{
			if (ft_strncmp(va_data->data, "?", 2) == 0)
				va_str = ft_itoa(g_exit_status);
			else
				va_str = insert_variable_data(var_arg, cmd);
			if (va_str)
			{
				move_variable_arguments_index(var_arg, va_str);
				new_arg = ft_str_insert(cmd->arguments[va_data->arg_nb],
						va_str, va_data->arg_idx);
				free(va_str);
				free(cmd->arguments[va_data->arg_nb]);
				cmd->arguments[va_data->arg_nb] = new_arg;
			}
		}
		var_arg = var_arg->next;
	}
}

static void	convert_wildcards(t_command *command)
{
	t_variable_argument	*var_arg_data;
	t_list				*var_arg;
	size_t				arg_number;

	arg_number = 0;
	while (command->arguments[arg_number])
	{
		var_arg = command->argument_variables;
		while (var_arg)
		{
			var_arg_data = var_arg->content;
			if (var_arg_data->arg_nb == arg_number
				&& var_arg_data->type == WILDCARD)
				break ;
			var_arg = var_arg->next;
		}
		if (var_arg)
			manage_wildcard(var_arg, command);
		arg_number++;
	}
}

void	convert_variable_arguments(t_command *command)
{
	convert_env_var(command->argument_variables, command);
	convert_wildcards(command);
}
