/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:39:42 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/15 15:22:04 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

	pass = ft_pwd();
	if (!pass)
		return (NULL);
	home = getenv("HOME");
	if (home)
	{
		path = strdup(pass + strlen(home) - 1);
		path[0] = '~';
		free(pass);
		return (path);
	}
	return (pass);
}
