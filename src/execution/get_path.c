/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 19:13:09 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/31 13:22:21 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**create_path(char **env)
{
	int		i;
	char	*tmp;
	char	**path;

	i = 0;
	while (env[i] != NULL && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (env[i] == NULL)
		return (NULL);
	path = ft_split(env[i] + 5, ':');
	i = 0;
	while (path[i])
	{
		if (path[i][0] && path[i][ft_strlen(path[i]) - 1] != '/')
		{
			tmp = ft_strjoin(path[i], "/");
			if (tmp)
			{
				free(path[i]);
				path[i] = tmp;
			}
		}
		i++;
	}
	return (path);
}

char	*find_cmd(char *cmd, char **env)
{
	int		i;
	char	*tmp;
	char	**path;

	path = create_path(env);
	if (access(cmd, X_OK) != -1)
		return (ft_strdup(cmd));
	if (!path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], cmd);
		if (access(tmp, X_OK) != -1)
		{
			ft_free_strs(path);
			return (tmp);
		}
		free(tmp);
		i++;
	}
	ft_free_strs(path);
	return (NULL);
}
