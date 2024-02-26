/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_create_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:39:23 by babonnet          #+#    #+#             */
/*   Updated: 2024/02/26 21:12:40 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include <fcntl.h>

void	add_here_doc_data(t_infile *infile, int fd_file, char *file_name)
{
	close(fd_file);
	infile->fd = open(file_name, O_RDONLY);
	unlink(file_name);
	free(file_name);
}
