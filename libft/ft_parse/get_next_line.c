/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:22:17 by psalame           #+#    #+#             */
/*   Updated: 2024/01/13 11:09:31 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*gnl_read(int fd)
{
	char	*buffer;
	char	*str;
	ssize_t	len;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	buffer[0] = 0;
	str = NULL;
	while (1)
	{
		len = ft_read_to_cstr(fd, buffer);
		if (len == -1)
		{
			if (str)
				free(str);
			free(buffer);
			return (NULL);
		}
		str = ft_strfjoin(str, buffer);
		if (len < BUFFER_SIZE || ft_strchr(buffer, '\n') != NULL)
			break ;
	}
	free(buffer);
	return (str);
}

static char	*gnl_get_line(char *full_buffer, char **oldstr)
{
	size_t	i;

	i = 0;
	while (full_buffer[i] && full_buffer[i] != '\n')
		i++;
	if (!full_buffer[i])
	{
		*oldstr = NULL;
		return (full_buffer);
	}
	else
	{
		*oldstr = ft_strdup(full_buffer + i + 1);
		full_buffer[i + 1] = 0;
		return (full_buffer);
	}
}

static char	*gnl_process(int fd, bool close)
{
	static char	*oldstr[1024];
	char		*readed;
	char		*line;

	if (close)
		free(oldstr[fd]);
	else
	{
		readed = NULL;
		if (oldstr[fd] == NULL || ft_strchr(oldstr[fd], '\n') == NULL)
			readed = gnl_read(fd);
		if (oldstr[fd] == NULL && readed == NULL)
			return (NULL);
		line = ft_strfjoin(oldstr[fd], readed);
		if (readed != NULL)
			free(readed);
		if (line == NULL || line[0] == 0)
		{
			free(line);
			oldstr[fd] = NULL;
		}
		else
			return (gnl_get_line(line, oldstr + fd));
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	else
		return (gnl_process(fd, false));
}

void	close_next_line(int fd)
{
	if (fd >= 0 && fd < 1024)
		gnl_process(fd, true);
}
