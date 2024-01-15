/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:39:42 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/15 16:22:47 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

char	*ft_pwd(void)
{
	static int	buffer_size = 1;
	char		*res;
	char		*buff;

	buff = malloc(buffer_size);
	if (!buff)
		return (NULL);
	res = getcwd(buff, buffer_size);
	while (res != buff)
	{
		buffer_size *= 2;
		free(buff);
		buff = malloc(buffer_size);
		if (!buff)
			return (NULL);
		res = getcwd(buff, buffer_size);
	}
	return (buff);
}

char	*get_path(void)
{
	char	*pass;
	char	*home;
	char	*path;
	int		home_len;

	pass = ft_pwd();
	if (!pass)
		return (NULL);
	home = getenv("HOME");
	if (!home || !home[0])
		return (pass);
	home_len = ft_strlen(home);
	if (ft_strncmp(pass, home, home_len))
		return (pass);
	if (home[home_len - 1] == '/' || !(pass[home_len] == '/' || pass[home_len] == 0))
		return (pass);
	path = ft_strdup(pass + home_len - 1);
	path[0] = '~';
	free(pass);
	return (path);
}
