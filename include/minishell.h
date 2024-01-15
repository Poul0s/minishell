/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:18:36 by psalame           #+#    #+#             */
/*   Updated: 2024/01/15 14:55:29 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "command.h"
# include "libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <sys/stat.h>
# include <unistd.h>

typedef struct s_sh_data
{
	char	*prompt;
	char	*hostname;
}			t_sh_data;

char	*get_hostname(void);
char	*ft_pwd(void);
void	refresh_prompt(t_sh_data *shell_data);


#endif
