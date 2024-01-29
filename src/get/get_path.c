/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:39:42 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/29 16:40:51 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	*get_path(void)
{
	char	*pass;
	char	*home;
	char	*path;
	int		home_len;

	pass = return_pwd();
	if (!pass)
		return (NULL);
	home = getenv("HOME");
	if (!home || !home[0])
		return (pass);
	home_len = ft_strlen(home);
	if (ft_strncmp(pass, home, home_len))
		return (pass);
	if (home[home_len - 1] == '/'
		|| !(pass[home_len] == '/' || pass[home_len] == 0))
		return (pass);
	path = ft_strdup(pass + home_len - 1);
	path[0] = '~';
	free(pass);
	return (path);
}
