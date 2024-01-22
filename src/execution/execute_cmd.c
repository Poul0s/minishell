/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:23:43 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/22 16:23:47 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <errno.h>

static char	*ft_str_insert(char *src, char *str, size_t pos)
{
	char	*dest;
	size_t	dest_len;
	size_t	i;

	dest_len = ft_strlen(src) + ft_strlen(str) + 1;
	dest = malloc(dest_len * sizeof(char));
	if (!dest)
		return (dest);
	dest[0] = 0;
	i = 0;
	if (pos < ft_strlen(src))
	{
		ft_strlcat(dest, src, pos + 1);
		ft_strlcat(dest, str, dest_len);
		ft_strlcat(dest, src + pos, dest_len);
	}
	else
	{
		ft_strlcat(dest, src, dest_len);
		ft_strlcat(dest, str, dest_len);
	}
	return (dest);
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
				var_arg_str = ft_strdup(get_env_value(env->env, var_arg_data->data)); // todo reuse function insert_variable_data to insert multiple argument variable
		}
		else
		{
			// todo add wildcard
		}
		new_arg = ft_str_insert(command->arguments[var_arg_data->argument_number],
								var_arg_str,
								var_arg_data->argument_index);
		free(var_arg_str);
		// todo add way to free new_arg (maybe add a cache)
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
			exit(127);
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
