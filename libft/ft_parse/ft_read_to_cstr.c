/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_to_cstr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 17:51:08 by psalame           #+#    #+#             */
/*   Updated: 2023/11/19 17:55:44 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	ft_read_to_cstr(int fd, char *buffer)
{
	ssize_t	res;

	if (buffer == NULL)
		return (-1);
	res = read(fd, buffer, BUFFER_SIZE);
	if (buffer == NULL || res == -1)
		return (-1);
	buffer[res] = 0;
	return (res);
}
