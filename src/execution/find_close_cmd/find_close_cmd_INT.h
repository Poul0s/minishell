/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_close_cmd_INT.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 23:39:26 by babonnet          #+#    #+#             */
/*   Updated: 2024/02/27 23:41:18 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIND_CLOSE_CMD_INT_H
# define FIND_CLOSE_CMD_INT_H

# include "environment_manager.h"
# include "ft_string.h"
# include "libft.h"
# include <dirent.h>

int		min_of_3(int a, int b, int c);
void	free_matrix(int **matrix, int s1);
bool	is_allready_there(t_list *head, char *str);
int		**init_matrix(int w1_len, int w2_len);

#endif
