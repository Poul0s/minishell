/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:23:43 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/23 01:27:20 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ft_print.h"
#include <errno.h>

static char	**ft_strs_insert_str(char **src, char *new_elem, size_t pos)
{
	size_t	i;
	size_t	j;
	char	**res;
	size_t	res_size;

	res_size = ft_strs_len(src) + 1;
	res = malloc((res_size + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (i < res_size)
	{
		if (i == pos)
			res[i] = new_elem;
		else
			res[i] = src[j++];
		i++;
	}
	res[i] = NULL;
	return (res);
}

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
	if (!new_argument_list)
	{
		free(argument);
		return ;
	}
	// todo add new_argument_list (but not each str in it) in cache alloc
	command->arguments = new_argument_list;
}

static char	*insert_variable_data(t_list *variable_argument, t_command *command, t_env_tree *env)
{
	t_variable_argument	*var_arg_data;
	char				**var_arg_strs;
	char				*res;
	size_t				i;

	var_arg_data = variable_argument->content;
	var_arg_strs = ft_split(get_env_value(env->env, var_arg_data->data), ' ');
	if (!var_arg_strs || var_arg_strs[0] == NULL)
	{
		free(var_arg_strs);
		return (NULL);
	}
	i = 0;
	while (var_arg_strs[i] && var_arg_strs[i + 1])
	{
		// todo add var_arg_strs[i] in cache alloc
		insert_argument(variable_argument, command, var_arg_strs[i]);
		i++;
	}
	res = var_arg_strs[i];
	free(var_arg_strs);
	return (res);
}

static void	convert_variable_arguments(t_command *command, t_env_tree *env, int exit_status)
{
	t_list				*variable_argument;
	t_variable_argument	*var_arg_data;
	char				*var_arg_str;
	char				*new_arg;

	variable_argument = command->argument_variables;
	while (variable_argument != NULL)
	{
		var_arg_data = variable_argument->content;
		if (var_arg_data->type == ENVIRONMENT_VARIABLE)
		{
			if (ft_strncmp(var_arg_data->data, "?", 2) == 0)
				var_arg_str = ft_itoa(exit_status);
			else if (env != NULL)
				var_arg_str = insert_variable_data(variable_argument, command, env); // todo reuse function insert_variable_data to insert multiple argument variable
		}
		else
		{
			// todo add wildcard
		}
		new_arg = ft_str_insert(command->arguments[var_arg_data->argument_number],
								var_arg_str,
								var_arg_data->argument_index);
		free(var_arg_str);
		// todo add way to free new_arg (maybe add a alloc cache)
		///		if another insert in same arg
		///		 at the end of execution of function 'execute_command'
		command->arguments[var_arg_data->argument_number] = new_arg;
		variable_argument = variable_argument->next;
	}
}

int	execute_command(t_command *command, t_command_group *group_data, int fd[2], int exit_status)
{
	int		child_pid;
	int		baby_pid;
	int		child_pid_res;

	convert_variable_arguments(command, group_data->env, exit_status);
	command->executable = command->arguments[0];
	baby_pid = -1;
	child_pid = fork();
	if (child_pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		command->executable = find_cmd(command->executable, convert_env_data_to_strs(group_data->env->env));
		if (command->executable == NULL)
		{
			ft_dprintf(2, "%s: command not found\n",command->arguments[0]);
			find_close_cmd(command->arguments[0]);
			exit(127);
		}
		execve(command->executable, command->arguments, convert_env_data_to_strs(group_data->env->env)); // todo add premake of char **env in t_env_data for free at end
		exit(errno);
	}
	else if (group_data->on_success || group_data->on_error)
	{
		waitpid(child_pid, &child_pid_res, 0);
		baby_pid = fork();
		if (baby_pid == 0)
		{
			child_pid_res = WEXITSTATUS(child_pid_res);
			if (child_pid_res != 0 && group_data->on_error != NULL)
					exit(execute_command_line(group_data->on_error, child_pid_res));
			else if (child_pid_res == 0 && group_data->on_success != NULL)
					exit(execute_command_line(group_data->on_success, child_pid_res));
			exit(child_pid_res);
		}
		else
			return (baby_pid);
	}
	return (child_pid);
}
