/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:02:49 by psalame           #+#    #+#             */
/*   Updated: 2024/02/28 19:34:16 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_BONUS_H
# define EXECUTION_BONUS_H

# include "command_bonus.h"
# include <sys/types.h>
# include <sys/wait.h>

typedef int	(*t_builtin_function)(t_command *);

typedef struct s_pipe
{
	int		fd[2][2];
	int		index;
	int		pipe_count;
}			t_pipe;

bool		is_command_builtin(char *command);
int			execute_builtin_command(t_command *command);

int			execute_command(t_command *command, t_command_group *group_data,
				int fd[2]);

void		pipe_cmd(t_command_group *command_line, t_execution_data exec_data,
				t_pipe *data_pipe);
int			manage_infile(t_list *infile, int fd);
int			manage_outfile(t_list *outfiles, int fd);
int			manage_iofiles(t_command *command);

int			execute_command_line(t_command_group *command_line,
				t_execution_data exec_data);
char		*find_cmd(char *cmd, char **env, int *error_res);
void		*find_close_cmd(const char *cmd, char **env);
int			get_pid_res(int pid);

#endif
