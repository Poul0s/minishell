/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:41:11 by babonnet          #+#    #+#             */
/*   Updated: 2024/02/28 18:33:16 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_manager.h"
#include "ft_print.h"
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

static int	too_many_cd_args(char *arg, char *program_name)
{
	if (!arg)
		return (0);
	ft_dprintf(2, "%s: cd: too many arguments\n", program_name);
	return (1);
}

static char	*cd_arg(char *arg, char ***env, char *program_name)
{
	char	*old_pwd;
	char	*pwd;

	if (ft_strncmp(arg, "-", ft_strlen(arg)) || !*arg)
		return (ft_strdup(arg));
	old_pwd = get_env_var(*env, "OLDPWD");
	if (!old_pwd || !*old_pwd)
	{
		ft_dprintf(2, "%s: cd: OLDPWD not set\n", program_name);
		return (NULL);
	}
	pwd = return_pwd();
	if (chdir(old_pwd) == -1)
	{
		ft_dprintf(2, "%s: cd: %s: No such file or directory\n", program_name,
			old_pwd);
		free(pwd);
		return (NULL);
	}
	printf("%s\n", old_pwd);
	*env = edit_env_var(*env, "PWD", old_pwd);
	*env = edit_env_var(*env, "OLDPWD", pwd);
	free(pwd);
	return ("");
}

static int	_cd(char *final_path, char ***env, char *program_name)
{
	char	*old_pwd;
	char	*pwd;

	old_pwd = return_pwd();
	if (chdir(final_path) == -1)
	{
		if (access(final_path, F_OK))
			ft_dprintf(2, "%s: cd: %s: No such file or directory\n",
				program_name, final_path);
		else
			ft_dprintf(2, "%s: cd: %s: Permission denied\n",
				program_name, final_path);
		free(final_path);
		return (1);
	}
	pwd = return_pwd();
	*env = edit_env_var(*env, "PWD", pwd);
	*env = edit_env_var(*env, "OLDPWD", old_pwd);
	free(pwd);
	free(old_pwd);
	free(final_path);
	return (0);
}

int	ft_cd(t_command *command)
{
	char	*final_path;
	char	**path;
	char	***env;
	char	*program_name;

	program_name = command->exec_data.shell_data->exec_name;
	path = command->arguments;
	env = command->env;
	if (!path)
		return (127);
	else if (path[0] && !path[1])
		final_path = get_home_path(*env);
	else if (path[0] && !*path[1])
		return (0);
	else if (too_many_cd_args(path[2], program_name))
		return (1);
	else
		final_path = cd_arg(path[1], env, program_name);
	if (!final_path || !path[1])
		return (1);
	if (!*final_path)
		return (0);
	return (_cd(final_path, env, program_name));
}
