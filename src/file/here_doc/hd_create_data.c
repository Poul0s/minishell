/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_create_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:39:23 by babonnet          #+#    #+#             */
/*   Updated: 2024/02/06 18:58:53 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "command.h"
#include "here_doc.h"

void add_here_doc_data(t_list **head, int fd_file, char *file_name)
{
	t_infile *infile;

	ft_lstclear(head, pop_infile);
	infile = malloc(sizeof(t_infile));
	if (!infile)
		return ;
	infile->filename = file_name;
	infile->fd = fd_file;
	infile->here_doc = true;
	infile->delimiter = NULL;
	*head = ft_lstnew(infile);
}

void add_file_data(t_list **head, int fd_file)
{
	t_infile *infile;

	infile = malloc(sizeof(t_infile));
	if (!infile)
		return ;
	ft_lstclear(head, pop_infile);
	infile->filename = NULL;
	infile->fd = fd_file;
	infile->here_doc = false;
	infile->delimiter = NULL;
	*head = ft_lstnew(infile);	
}
