/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompleion.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:20:55 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/17 16:35:26 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOCOMPLETION_H
#define AUTOCOMPLETION_H

# include "libft.h"
# include <readline/readline.h>

t_list		*find_match_cmd(const char *start_cmd);
t_list		*find_match_file(const char *start_cmd);
char		*wich_word(void);
t_list		*autocompletion_dir(const char *path);
char		*autocompletion(const char *str, int status);

#endif
