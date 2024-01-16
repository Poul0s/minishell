/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:18:36 by psalame           #+#    #+#             */
/*   Updated: 2024/01/16 19:06:27 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include "command.h"
# include "libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/stat.h>
# include <unistd.h>

typedef struct s_sh_data
{
	char	*prompt;
	char	*hostname;
}			t_sh_data;

char		*get_hostname(void);
void		refresh_prompt(t_sh_data *shell_data);
char		*return_pwd(void);
char		*get_path(void);

t_list		*find_match_cmd(const char *start_cmd);
t_list		*find_match_file(const char *start_cmd);
char		*wich_word(void);
t_list		*autocompletion_dir(const char *path);
char		*autocompletion(const char *str, int status);

void		print_command_line(t_command_group *command, int depth);

void	init_signal_handler(void);

int			ft_cd(const char *path);
int			ft_env(const char **env);
int			ft_echo(const char *strs);
#endif
