/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_close_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 01:21:22 by babonnet          #+#    #+#             */
/*   Updated: 2024/02/28 18:29:48 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "find_close_cmd_INT.h"

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
		return (3);
	result = find_distance(matrix, word1, word2);
	free_matrix(matrix, w1_len);
	return (result);
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

void	find_close_cmd(const char *cmd, char **env)
{
	char	*path;
	char	**paths;
	char	**paths_cpy;
	t_list	*head;
	t_list	*node;

	head = NULL;
	path = get_env_var(env, "PATH");
	paths = ft_split(path, ':');
	if (!paths)
		return ;
	paths_cpy = paths;
	while (*paths)
		find_match_from_dir(&head, *paths++, cmd);
	ft_free_strs(paths_cpy);
	node = head;
	while (node)
	{
		if (ft_strlen(node->content) > 1)
			ft_dprintf(2, "	do you mean :%s\n", node->content);
		node = node->next;
	}
	ft_lstclear(&head, free);
}
