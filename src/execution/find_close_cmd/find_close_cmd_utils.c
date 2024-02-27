/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_close_cmd_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 23:35:19 by babonnet          #+#    #+#             */
/*   Updated: 2024/02/27 23:37:19 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	min_of_3(int a, int b, int c)
{
	if (a < b && a < c)
		return (a);
	else if (b < a && b < c)
		return (b);
	return (c);
}

void	free_matrix(int **matrix, int s1)
{
	if (!matrix)
		return ;
	while (s1 >= 0)
	{
		free(matrix[s1]);
		s1--;
	}
	free(matrix);
}

bool	is_allready_there(t_list *head, char *str)
{
	while (head)
	{
		if (!ft_strncmp(head->content, str, ft_strlen(head->content)))
			return (true);
		head = head->next;
	}
	return (false);
}

int	**init_matrix(int w1_len, int w2_len)
{
	int	**matrix;
	int	i;

	matrix = ft_calloc((w1_len + 1), sizeof(int *));
	if (!matrix)
		return (NULL);
	i = 0;
	while (i < (w1_len + 1))
	{
		matrix[i] = malloc((w2_len + 1) * sizeof(int));
		if (!matrix[i])
		{
			free_matrix(matrix, w1_len);
			return (NULL);
		}
		i++;
	}
	i = -1;
	while (++i < w2_len + 1)
		matrix[w1_len][i] = w2_len - i;
	i = -1;
	while (++i < w1_len + 1)
		matrix[i][w2_len] = w1_len - i;
	return (matrix);
}
