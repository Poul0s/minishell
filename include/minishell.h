/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:18:36 by psalame           #+#    #+#             */
/*   Updated: 2024/01/18 22:22:38 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include "command.h"
# include "environment_manager.h"
# include "libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/stat.h>
# include <unistd.h>

typedef struct s_sh_data
{
	char		*prompt;
	char		*hostname;
	t_env_tree	*env;
}			t_sh_data;

char		*get_hostname(void);
void		refresh_prompt(t_sh_data *shell_data);
char		*return_pwd(void);
char		*get_path(void);

void		print_command_line(t_command_group *command, int depth);

void	init_signal_handler(void);

int			ft_cd(const char *path);
int			ft_env(const char **env);
int			ft_echo(const char *strs);
#endif
