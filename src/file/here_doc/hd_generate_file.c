/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_generate_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:36:57 by babonnet          #+#    #+#             */
/*   Updated: 2024/02/26 20:52:54 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>

char	*create_tmp_file(int *fd)
{
	char	*file;
	int		fd_random;

	fd_random = open("/dev/random", O_RDONLY);
	if (fd_random == -1)
		return (NULL);
	file = ft_calloc(20, sizeof(char));
	if (!file)
	{
		close(fd_random);
		return (NULL);
	}
	while (1)
	{
		if (read(fd_random, file, 20) == -1)
			return (NULL);
		file[0] = '.';
		file[19] = '\0';
		*fd = open(file, O_CREAT | O_EXCL | O_WRONLY, 0644);
		if (*fd != -1)
		{
			close(fd_random);
			return (file);
		}
	}
}
