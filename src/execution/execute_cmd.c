/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 21:00:20 by babonnet          #+#    #+#             */
/*   Updated: 2024/02/27 16:40:33 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_Int.h"
#include "here_doc.h"
#include "minishell.h"
#include <errno.h>
#include <unistd.h>

static void	free_all_minishell(t_command *command)
{
	free(command->exec_data.pid);
	free_shell_data(command->exec_data.shell_data, false);
	free_command_line(command->exec_data.base_command_line, false);
	free_command_line(NULL, true);
}

static void	try_execute_bin_cmd(t_command *command, int file_error)
{
	if (command->executable == NULL)
	{
		ft_dprintf(2, "%s: command not found\n", command->arguments[0]);
		find_close_cmd(command->arguments[0]);
	}
	else if (!file_error)
	{
		execve(command->executable, command->arguments,
			*(command->env));
		ft_dprintf(2, "%s: %s: %s\n",
			command->exec_data.shell_data->exec_name,
			command->arguments[0], strerror(errno));
	}
}

static int	execute_binary_command(t_command *command, int fd[2])
{
	int	pid;
	int	file_error;

	command->executable = find_cmd(command->executable, *(command->env));
	pid = fork();
	if (pid == 0)
	{
		if (fd != NULL)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
		}
		file_error = manage_infile(command->infiles, STDIN_FILENO);
		if (!file_error)
			file_error = manage_outfile(command->outfiles, STDOUT_FILENO);
		try_execute_bin_cmd(command, file_error);
		free(command->executable);
		free_all_minishell(command);
		exit(127);
	}
	free(command->executable);
	return (pid);
}

static void	execute_cmd_operator(t_command *cmd,
								t_command_group *grp_data,
								int *child_pid_res)
{
	int	forked;

	if ((*child_pid_res != 0 && grp_data->on_error != NULL)
		|| (*child_pid_res == 0 && grp_data->on_success != NULL))
	{
		forked = cmd->exec_data.forked;
		cmd->exec_data.forked = false;
		if (*child_pid_res != 0 && grp_data->on_error != NULL)
			*child_pid_res = execute_command_line(grp_data->on_error,
					cmd->exec_data);
		else if (*child_pid_res == 0 && grp_data->on_success != NULL)
			*child_pid_res = execute_command_line(grp_data->on_success,
					cmd->exec_data);
		cmd->exec_data.forked = forked;
	}
}

int	execute_command(t_command *command, t_command_group *group_data, int fd[2])
{
	int	child_pid;
	int	child_pid_res;

	convert_variable_arguments(command);
	command->executable = command->arguments[0];
	if (is_command_builtin(command->executable))
		child_pid = execute_builtin_command(command);
	else
		child_pid = execute_binary_command(command, fd);
	if (child_pid < 0)
		child_pid_res = -child_pid - 1;
	else
		child_pid_res = get_pid_res(child_pid);
	execute_cmd_operator(command, group_data, &child_pid_res);
	if (command->exec_data.forked)
		free_all_minishell(command);
	return (child_pid_res);
}
