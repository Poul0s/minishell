/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_close_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 01:21:22 by babonnet          #+#    #+#             */
/*   Updated: 2024/02/26 21:30:24 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "libft.h"
#include <dirent.h>

static int	min_of_3(int a, int b, int c)
{
	if (a < b && a < c)
		return (a);
	else if (b < a && b < c)
		return (b);
	return (c);
}

static void	free_matrix(int **matrix, int s1)
{
	if (!matrix)
		return ;
	while (s1 > 0)
	{
		free(matrix[s1 - 1]);
		s1--;
	}
	free(matrix);
}

static int	**init_matrix(int w1_len, int w2_len)
{
	int	**matrix;
	int	i;

	matrix = malloc((w1_len + 1) * sizeof(int *));
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
	return (0);
}

static int	find_distance(int **matrix, char *word1, char *word2)
{
	int	i;
	int	j;
	int	w1_len;
	int	w2_len;

	w1_len = ft_strlen(word1);
	w2_len = ft_strlen(word2);
	i = w1_len - 1;
	while (i >= 0)
	{
		j = w2_len - 1;
		while (j >= 0)
		{
			if (word1[i] == word2[j])
				matrix[i][j] = matrix[i + 1][j + 1];
			else
				matrix[i][j] = 1 + min_of_3(matrix[i + 1][j], matrix[i][j + 1],
						matrix[i + 1][j + 1]);
			j--;
		}
		i--;
	}
	return (matrix[0][0]);
}

int	levenshtein(char *word1, char *word2)
{
	int	**matrix;
	int	w1_len;
	int	w2_len;
	int	result;

	w1_len = ft_strlen(word1);
	w2_len = ft_strlen(word2);
	matrix = init_matrix(w1_len, w2_len);
	if (!matrix)
		return (-1);
	result = find_distance(matrix, word1, word2);
	free_matrix(matrix, w1_len);
	return (result);
}

static bool	is_allready_there(t_list *head, char *str)
{
	while (head)
	{
		if (!ft_strncmp(head->content, str, ft_strlen(head->content)))
			return (true);
		head = head->next;
	}
	return (false);
}

static void	find_match_from_dir(t_list **head, char *pwd, const char *cmd)
{
	int				start_len;
	DIR				*dir;
	struct dirent	*dirent;

	if (!pwd || !cmd)
		return ;
	dir = opendir(pwd);
	if (!dir)
		return ;
	dirent = readdir(dir);
	start_len = ft_strlen(cmd);
	(void)start_len;
	while (dirent)
	{
		if (levenshtein((char *)cmd, dirent->d_name) < 2
			&& !is_allready_there(*head, dirent->d_name))
			ft_lstadd_front(head, ft_lstnew(ft_strdup(dirent->d_name)));
		dirent = readdir(dir);
	}
	closedir(dir);
}

void	find_close_cmd(const char *cmd)
{
	char	*env;
	char	**paths;
	char	**paths_cpy;
	t_list	*head;

	head = NULL;
	env = getenv("PATH");
	paths = ft_split(env, ':');
	if (!paths)
		return ;
	paths_cpy = paths;
	while (*paths)
	{
		find_match_from_dir(&head, *paths, cmd);
		paths++;
	}
	ft_free_strs(paths_cpy);
	while (head)
	{
		ft_dprintf(2, "	do you mean :%s\n", head->content);
		head = head->next;
	}
	ft_lstclear(&head, free);
}
