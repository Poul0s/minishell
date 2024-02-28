/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_iofile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:18:31 by psalame           #+#    #+#             */
/*   Updated: 2024/02/28 19:37:38 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_bonus.h"

void	free_infile(void *data)
{
	t_infile	*infile;

	infile = data;
	if (infile->here_doc)
		free(infile->delimiter);
	else
		free(infile->filename);
	free(infile);
}

void	free_outfile(void *data)
{
	t_infile	*infile;

	infile = data;
	free(infile->filename);
	free(infile);
}
