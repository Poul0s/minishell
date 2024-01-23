/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_close_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 01:21:22 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/23 01:59:08 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "libft.h"

int min_of_3(int a, int b, int c)
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

int levenshtein(char *word1, char *word2)
{
	int **matrix;
	int w1_len;
	int w2_len;
	int i;
	int j;

	w1_len = ft_strlen(word1);
	w2_len = ft_strlen(word2);
	matrix = malloc((w1_len + 1) * sizeof(int *));
	if (!matrix)
		return (-1);
	i = 0;
	while (i < (w1_len + 1))
	{
		matrix[i] = malloc((w2_len + 1) * sizeof(int));
		if (!matrix[i])
		{
			free_matrix(matrix, w1_len);
			return (-1);
		}
		i++;
	}
	i = -1;
	while (++i < w2_len + 1)
		matrix[w1_len][i] = w2_len - i;
	i = -1;
	while (++i < w1_len + 1)
		matrix[i][w2_len] = w1_len - i;
	i = w1_len - 1;
	while (i >= 0)
	{
		j = w2_len - 1;
		while (j >= 0)
		{
			if (word1[i] == word2[j])
				matrix[i][j] = matrix[i + 1][j + 1];
			else
				matrix[i][j] = 1 + min_of_3(matrix[i + 1][j], matrix[i][j + 1], matrix[i + 1][j + 1]);
			j--;
		}
		i--;
	}
	i = matrix[0][0];
	free_matrix(matrix, w1_len);
	return (i);	
}

static bool is_allready_there(t_list *head, char *str)
{
	while(head)
	{
		if (!ft_strncmp(head->content, str, ft_strlen(head->content)))
			return (true);
		head = head->next;
	}
	return (false);
}

static void	find_match_from_dir(t_list **head, char *pwd, const char *cmd)
{
	int		start_len;
	DIR		*dir;
	struct dirent  *dirent;

	if (!pwd || !cmd)
		return ;
	dir = opendir(pwd);
	if (!dir)
		return ;
	dirent = readdir(dir);
	start_len = ft_strlen(cmd);
	(void)start_len;
	while(dirent)
	{
		if (levenshtein((char *)cmd, dirent->d_name) < 2 && !is_allready_there(*head, dirent->d_name))
			ft_lstadd_front(head, ft_lstnew(ft_strdup(dirent->d_name)));
		dirent = readdir(dir);
	}
	closedir(dir);
}

static void	free_split(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i])
	{
		if (strs[i])
			free(strs[i]);
		i++;
	}
	free(strs);
}

static void pop(void *content)
{
	free(content);
}

void find_close_cmd(const char *cmd)
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
	while(*paths)
	{
		find_match_from_dir(&head, *paths, cmd);
		paths++;
	}
	free_split(paths_cpy);
	while (head)
	{
		ft_printf("	do you mean :%s\n", head->content);
		head = head->next;
	}
	ft_lstclear(&head, pop);
}
