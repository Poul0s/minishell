/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:32:53 by babonnet          #+#    #+#             */
/*   Updated: 2024/02/26 20:48:48 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_H
# define HERE_DOC_H

#include "command.h"

void	manage_here_doc(t_command_group *g_cmd, int *error);
void	close_all_fd(t_command_group *g_cmd);

char	*create_tmp_file(int *fd);
void	add_here_doc_data(t_infile *infile, int fd_file, char *file_name);

void	pop_infile(void *content);

#endif
