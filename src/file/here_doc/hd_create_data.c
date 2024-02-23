/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_create_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:39:23 by babonnet          #+#    #+#             */
/*   Updated: 2024/02/22 16:10:14 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "command.h"
#include "here_doc.h"
#include <fcntl.h>
#include <unistd.h>

void add_here_doc_data(t_infile *infile, int fd_file, char *file_name)
{
	close(fd_file);
	infile->fd = open(file_name, O_RDONLY);
	unlink(file_name);
}
