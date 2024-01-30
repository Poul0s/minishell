/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:23:43 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/30 11:40:29 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

extern int	g_exit_status;

char	**ft_strs_insert_str(char **src, char *new_elem, size_t pos)
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

static void	convert_variable_arguments(t_command *command)
{
	t_list				*variable_argument;
	t_variable_argument	*var_arg_data;
	char				*var_arg_str;
	char				*new_arg;

	variable_argument = command->argument_variables;
	while (variable_argument != NULL)
	{
		var_arg_data = variable_argument->content;
		if (var_arg_data->type == ENV_VAR)
		{
			if (ft_strncmp(var_arg_data->data, "?", 2) == 0)
				var_arg_str = ft_itoa(g_exit_status);
			else
				var_arg_str = insert_variable_data(variable_argument, command);
		}
		else
		{
			// todo add wildcard
		}
		if (var_arg_str)
		{
			move_variable_arguments_index(variable_argument, var_arg_str);
			new_arg = ft_str_insert(command->arguments[var_arg_data->argument_number],
									var_arg_str,
									var_arg_data->argument_index);
			free(var_arg_str);
			free(command->arguments[var_arg_data->argument_number]);
			command->arguments[var_arg_data->argument_number] = new_arg;
		}
		variable_argument = variable_argument->next;
	}
}

int	execute_command(t_command *command, t_command_group *group_data, int fd[2])
{
	int		child_pid;
	int		baby_pid;
	int		child_pid_res;

	convert_variable_arguments(command);
	command->executable = command->arguments[0];
	baby_pid = -1;
	if (is_command_builtin(command->executable))
		child_pid = execute_builtin_command(command);
	else
	{
		command->executable = find_cmd(command->executable, *(command->env));
		child_pid = fork();
		if (child_pid == 0)
		{
			if (fd != NULL)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
			}
			if (command->executable == NULL)
			{
				ft_dprintf(2, "%s: command not found tes\n",command->arguments[0]);
				find_close_cmd(command->arguments[0]);
				exit(127);
			}
			execve(command->executable, command->arguments, *(command->env));
			exit(errno);
		}
		free(command->executable);
	}
	if (!command->last_pipe_cmd && child_pid != 0 && (group_data->on_success || group_data->on_error))
	{
		if (child_pid < 0)
			child_pid_res = (-child_pid - 1) >> 8;
		else
			waitpid(child_pid, &child_pid_res, 0);
		if ((g_exit_status != 0 && group_data->on_error != NULL) || (g_exit_status == 0 && group_data->on_success != NULL))
		{
			baby_pid = fork();
			if (baby_pid == 0)
			{
				// command->exec_data.forked = false;
				free(command->exec_data.pid);
				g_exit_status = WEXITSTATUS(child_pid_res);
				if (g_exit_status != 0 && group_data->on_error != NULL)
						exit(execute_command_line(group_data->on_error, command->exec_data));
				else if (g_exit_status == 0 && group_data->on_success != NULL)
						exit(execute_command_line(group_data->on_success, command->exec_data));
				exit(g_exit_status);
			}
			else
			{
				// free_command(command);
				// return (baby_pid);
				child_pid = baby_pid;
			}
		}
	}
	if (command->exec_data.forked)
	{
		free(command->exec_data.pid);
		free_shell_data(command->exec_data.shell_data, false);
		free_command_line(command->exec_data.base_command_line, false);
		free_command_line(NULL, true);
	}
	return (child_pid);
}
