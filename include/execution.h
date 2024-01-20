/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:02:49 by psalame           #+#    #+#             */
/*   Updated: 2024/01/20 18:39:06 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "command.h"
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_pipe
{
	int	fd[2][2];
	int	index;
	int	pipe_count;
}		t_pipe;

int		execute_command(t_command *command, t_command_group *group_data,
			int fd[2]);
void	pipe_cmd(t_command_group *command_line, int *pid, t_pipe *data_pipe);
int		execute_command_line(t_command_group *command_line);
char	*find_cmd(char *cmd, char **path);

#endif
