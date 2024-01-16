/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:27:43 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/15 19:37:01 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*return_pwd(void)
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

int	ft_pwd(void)
{
	char *buff;

	buff = return_pwd();
	if (!buff)
		return (1);
	ft_printf("%s\n", buff);
	free(buff);
	return (0);
}
