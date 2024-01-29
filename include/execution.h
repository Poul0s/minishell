/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:02:49 by psalame           #+#    #+#             */
/*   Updated: 2024/01/29 15:33:38 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "command.h"
# include "minishell.h"
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_pipe
{
	int	fd[2][2];
	int	index;
	int	pipe_count;
}		t_pipe;

bool	is_command_builtin(char *command);
int		execute_builtin_command(t_command *command);

int		execute_command(t_command *command, t_command_group *group_data,
			int fd[2]);

void	pipe_cmd(t_command_group *command_line,
			t_execution_data exec_data,
			t_pipe *data_pipe);

int		execute_command_line(t_command_group *command_line,
			t_execution_data exec_data);
char	*find_cmd(char *cmd, char **path);
void	*find_close_cmd(const char *cmd);

#endif
