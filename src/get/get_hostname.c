/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hostname.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:15:14 by psalame           #+#    #+#             */
/*   Updated: 2024/01/27 09:10:25 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_hostname(void)
{
	char	*hostname;
	char	*hostname_end;
	int		fd;

	fd = open("/etc/hostname", O_RDONLY);
	hostname = get_next_line(fd);
	close_next_line(fd);
	hostname_end = ft_strchr(hostname, '.');
	if (hostname_end != 0)
		*hostname_end = 0;
	hostname_end = ft_strchr(hostname, '\n');
	if (hostname_end != 0)
		*hostname_end = 0;
	return (hostname);
}
