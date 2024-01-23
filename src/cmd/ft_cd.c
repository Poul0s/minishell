/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:41:11 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/23 22:49:08 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>

int	ft_cd(const char **path)
{
	if (path == NULL || path[1] == NULL)
		return (1);
	if (chdir(path[1]) == -1)
	{
		ft_dprintf(2, "cd: %s: %s\n", strerror(errno), path[1]);
		return (1);
	}
	return (0);
}
