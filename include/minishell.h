/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:18:36 by psalame           #+#    #+#             */
/*   Updated: 2024/01/29 14:48:22 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "command.h"
# include "environment_manager.h"
# include "execution.h"
# include "syntax.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/stat.h>
# include <unistd.h>

typedef struct s_sh_data
{
	char		*exec_name;
	char		*prompt;
	char		*hostname;
	char		**env;
}			t_sh_data;

char		*get_hostname(void);
void		refresh_prompt(t_sh_data *shell_data);
char		*return_pwd(void);
char		*get_path(void);
char		*get_exec_name(char *bin_path);


void		print_command_line(t_command_group *command, int depth);

void		toggle_signal_handler(bool toggle);

int			ft_cd(const char **path);
int			ft_env(char **env);
int			ft_echo(const char **strs);
int			ft_pwd(void);
int			ft_export(char **arguments, char ***env);
int			ft_unset(char **arguments, char ***env);
int			ft_exit(t_command *command);

void		free_command(t_command *command);
void		free_command_line(t_command_group *command_line, bool reset);

char		*ft_strfjoin_chr(char *s1, char c); // todo move in libft
void		free_shell_data(t_sh_data *shell_data, bool disable_Signal);

#endif
