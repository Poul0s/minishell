/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:20:55 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/18 22:23:55 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOCOMPLETION_H
# define AUTOCOMPLETION_H

# include "libft.h"
# include <readline/readline.h>

typedef struct s_word
{
	char *word;
	char *path;
} t_word;

t_list	*find_match_cmd(const char *start_cmd);
t_list	*find_match_file(t_word *word);
t_word	*wich_word(void);
t_list	*autocompletion_dir(const char *path);
char	*autocompletion(const char *str, int status);
int	is_first(void);

#endif
