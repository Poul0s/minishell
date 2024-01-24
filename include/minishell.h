/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:18:36 by psalame           #+#    #+#             */
/*   Updated: 2024/01/24 18:13:56 by psalame          ###   ########.fr       */
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
	int			exit_status;
	char		**env;
}			t_sh_data;

char		*get_hostname(void);
void		refresh_prompt(t_sh_data *shell_data);
char		*return_pwd(void);
char		*get_path(void);

void		print_command_line(t_command_group *command, int depth);

void		toggle_signal_handler(bool toggle);

int			ft_cd(const char **path);
int			ft_env(const char **env);
int			ft_echo(const char **strs);
int			ft_pwd(void);

void		free_command(t_command *command);
void		free_command_line(t_command_group *command_line, bool reset);

char		*ft_strfjoin_chr(char *s1, char c); // todo move in libft

#endif
