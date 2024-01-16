/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:41:11 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/15 19:01:19 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>

int	ft_cd(char *path)
{
	if (*path == 0)
		return (1);
	if (chdir(path) == -1)
	{
		ft_dprintf(2, "cd: %s: %s\n", strerror(errno), path);
		return (1);
	}
	return (0);
}
