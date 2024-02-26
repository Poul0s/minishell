/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:41:11 by babonnet          #+#    #+#             */
/*   Updated: 2024/02/24 16:36:35 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static char	*get_home_path(char **env)
{
	char	*path;
	char	**tmp;

	path = get_env_var(env, "HOME");
	if (!path)
		return (NULL);
	tmp = ft_split(path, ':');
	if (!tmp)
		return (NULL);
	path = ft_strdup(tmp[0]);
	ft_free_strs(tmp);
	return (path);
}

static int	_cd(char *final_path, char ***env)
{
	char	*old_pwd;
	char	*pwd;

	old_pwd = return_pwd();
	if (chdir(final_path) == -1)
	{
		ft_dprintf(2, "minishell: cd: %s: No such file or directory\n",
			final_path);
		free(final_path);
		return (1);
	}
	pwd = return_pwd();
	edit_env_var(*env, "PWD", pwd);
	edit_env_var(*env, "OLDPWD", old_pwd);
	free(pwd);
	free(old_pwd);
	free(final_path);
	return (0);
}

int	ft_cd(const char **path, char ***env)
{
	char	*final_path;

	// variable pwd and old pwd cd -
	if (!path)
		return (127);
	else if (path[0] && !path[1])
		final_path = get_home_path(*env);
	else if (path[2])
	{
		ft_dprintf(2, "minishell: cd: too many arguments\n");
		return (1);
	}
	else if (!ft_strncmp(path[1], "-", ft_strlen(path[1])))
		final_path = ft_strdup(get_env_var(*env, "OLDPWD"));	
	else
		final_path = ft_strdup(path[1]);
	return (_cd(final_path, env));
}
