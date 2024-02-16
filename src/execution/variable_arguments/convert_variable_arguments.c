/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_variable_arguments.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 21:25:10 by psalame           #+#    #+#             */
/*   Updated: 2024/02/16 01:27:17 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "command_Int.h"

extern int	g_exit_status;

static void	insert_argument(t_list *variable_arguments, t_command *command, char *argument)
{
	t_variable_argument	*var_arg_data;
	char				**new_argument_list;
	size_t				insert_pos;

	var_arg_data = variable_arguments->content;
	insert_pos = var_arg_data->argument_number;
	while (variable_arguments)
	{
		var_arg_data = variable_arguments->content;
		if (var_arg_data->argument_number >= insert_pos)
			var_arg_data->argument_number++;
		variable_arguments = variable_arguments->next;
	}
	new_argument_list = ft_strs_insert_str(command->arguments, argument, insert_pos);
	if (new_argument_list)
	{
		free(command->arguments);
		command->arguments = new_argument_list;
	}
	else
	{
		free(new_argument_list);
		free(argument);
	}
}

static char	*insert_variable_data(t_list *variable_argument, t_command *command)
{
	t_variable_argument	*var_arg_data;
	char				**var_arg_strs;
	char				*res;
	size_t				i;

	var_arg_data = variable_argument->content;
	if (var_arg_data->disable_multiple_args)
		res = ft_strdup(get_env_var(*(command->env), var_arg_data->data));
	else
	{
		var_arg_strs = ft_split(get_env_var(*(command->env), var_arg_data->data), ' ');
		if (!var_arg_strs || var_arg_strs[0] == NULL)
		{
			free(var_arg_strs);
			return (NULL);
		}
		i = 0;
		while (var_arg_strs[i] && var_arg_strs[i + 1])
		{
			insert_argument(variable_argument, command, var_arg_strs[i]);
			i++;
		}
		res = var_arg_strs[i];
		free(var_arg_strs);
	}
	return (res);
}

static void	move_variable_arguments_index(t_list *variable_arguments, char *var_arg_str)
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
		if (current_var_arg->argument_number == var_arg->argument_number)
		{
			if (current_var_arg->argument_index >= var_arg->argument_index)
				current_var_arg->argument_index += var_arg_len;
		}
		variable_arguments = variable_arguments->next;
	}
}

static void	convert_env_var(t_list *var_arg, t_command *command)
{
	t_variable_argument	*var_arg_data;
	char				*var_arg_str;
	char				*new_arg;
	
	while (var_arg)
	{
		var_arg_data = var_arg->content;
		if (var_arg_data->type == ENV_VAR)
		{
			if (ft_strncmp(var_arg_data->data, "?", 2) == 0)
				var_arg_str = ft_itoa(g_exit_status);
			else
				var_arg_str = insert_variable_data(var_arg, command);
			if (var_arg_str)
			{
				move_variable_arguments_index(var_arg, var_arg_str);
				new_arg = ft_str_insert(command->arguments[var_arg_data->argument_number],
										var_arg_str,
										var_arg_data->argument_index);
				free(var_arg_str);
				free(command->arguments[var_arg_data->argument_number]);
				command->arguments[var_arg_data->argument_number] = new_arg;
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
			if (var_arg_data->argument_number == arg_number 
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
