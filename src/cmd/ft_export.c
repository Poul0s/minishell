/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 21:03:09 by psalame           #+#    #+#             */
/*   Updated: 2024/01/24 22:18:34 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_manager.h"
#include <string.h>
#include <errno.h>

void	ft_strs_sort(char **strs)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (strs[i] && strs[i + 1])
	{
		j = i + 1;
		while (strs[j])
		{
			if (ft_strncmp(strs[i], strs[j], ft_strlen(strs[i] + 1)) > 0)
			{
				tmp = strs[i];
				strs[i] = strs[j];
				strs[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	print_env_sorted(char **env)
{
	char	**tmp_env;
	size_t	i;

	tmp_env = ft_strs_dup(env);
	if (tmp_env == NULL)
	{
		ft_dprintf(2, "minishell: export: %s\n", strerror(ENOMEM));
		return (ENOMEM);
	}
	ft_strs_sort(tmp_env);
	i = 0;
	while (tmp_env[i])
	{
		ft_printf("declare -x %s\n", tmp_env[i]);
		i++;
	}
	ft_free_strs(tmp_env);
	return (0);
}

static void	insert_multiple_env_var(char **arguments, char ***env)
{
	char	*sep_pos;
	size_t	i;

	i = 0;
	while (arguments[i])
	{
		sep_pos = ft_strchr(arguments[i], '=');
		if (sep_pos)
		{
			*sep_pos = '\0';
			*env = edit_env_var(*env, arguments[i], sep_pos + 1);
		}
	}
}

int	ft_export(char **arguments, char ***env)
{
	if (arguments[1] == NULL)
		return (print_env_sorted(*env));
	else
	{
		if (ft_strs_len(arguments) == 3
			&& ft_strchr(arguments[1], '=') == NULL
			&& ft_strchr(arguments[1], '=') == NULL)
			*env = edit_env_var(*env, arguments[1], arguments[2]);
		else
			insert_multiple_env_var(arguments + 1, env);
		return (0);
	}
}
