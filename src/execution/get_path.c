/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 19:13:09 by babonnet          #+#    #+#             */
/*   Updated: 2024/02/28 18:31:34 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>

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

static int	is_directory(char *cmd)
{
	int	fd;

	fd = open(cmd, O_RDWR);
	if (errno == EISDIR)
	{
		ft_dprintf(2, "minishell: %s: Is a directory\n", cmd);
		if (fd > 0)
			close(fd);
		return (1);
	}
	if (fd > 0)
		close(fd);
	return (0);
}

static char	*_find_cmd(char *cmd, char **env)
{
	int		i;
	char	*tmp;
	char	**path;

	if (is_directory(cmd))
		return ("");
	if (access(cmd, F_OK) != -1 && ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path = create_path(env);
	if (!path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], cmd);
		if (access(tmp, F_OK) != -1)
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

char	*find_cmd(char *cmd, char **env, int *error_res)
{
	char	*result;

	result = _find_cmd(cmd, env);
	if (!result)
	{
		ft_dprintf(2, "%s: command not found\n", cmd);
		return (NULL);
	}
	if (!*result)
	{
		*error_res = 126;
		return (NULL);
	}
	if (access(result, X_OK) == -1)
		*error_res = 126;
	return (result);
}
