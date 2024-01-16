/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:18:36 by psalame           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/01/16 00:51:40 by babonnet         ###   ########.fr       */
=======
/*   Updated: 2024/01/15 23:20:26 by psalame          ###   ########.fr       */
>>>>>>> 31c5ea3a28ab17f8e1874406f028015fe3907887
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

<<<<<<< HEAD
t_list		*find_match_cmd(const char *start_cmd);
=======
void	print_command_line(t_command_group *command, int depth);

>>>>>>> 31c5ea3a28ab17f8e1874406f028015fe3907887

int			ft_pwd(void);
int			ft_cd(char *path);
int			ft_env(char **env);
#endif
