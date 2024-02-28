/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:18:36 by psalame           #+#    #+#             */
/*   Updated: 2024/02/28 19:34:16 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H

# include "command_bonus.h"
# include "environment_manager_bonus.h"
# include "execution_bonus.h"
# include "libft.h"
# include "syntax_bonus.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/stat.h>
# include <unistd.h>

typedef struct s_sh_data
{
	char	*exec_name;
	char	*prompt;
	char	*hostname;
	char	**env;
}			t_sh_data;

char		*get_hostname(void);
void		refresh_prompt(t_sh_data *shell_data);
char		*return_pwd(void);
char		*get_path(char **env);
char		*get_exec_name(char *bin_path);

void		print_command_line(t_command_group *command, int depth);

void		toggle_signal_handler(bool toggle_handler,
				bool toggle_termios_print);

int			ft_cd(t_command *command);
int			ft_echo(t_command *command);
int			ft_env(t_command *command);
int			ft_pwd(t_command *command);
int			ft_export(t_command *command);
int			ft_unset(t_command *command);
int			ft_exit(t_command *command);

void		free_command(t_command *command);
void		free_command_line(t_command_group *command_line, bool reset);

void		free_shell_data(t_sh_data *shell_data, bool disable_Signal);

#endif
