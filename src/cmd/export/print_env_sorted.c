/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env_sorted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:58:05 by psalame           #+#    #+#             */
/*   Updated: 2024/02/05 18:23:36 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export_Int.h"

static void	ft_strs_sort(char **strs)
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

static void	print_env_value(char *env_val)
{
	char	*value;

	value = ft_strchr(env_val, '=');
	ft_printf("declare -x ");
	if (value != NULL)
	{
		*value = 0;
		ft_printf("%s=\"%s\"\n", env_val, value + 1);
	}
	else
		ft_printf("%s\n", env_val);
}

int	print_env_sorted(char **env, char *shell_name)
{
	char	**tmp_env;
	size_t	i;

	tmp_env = ft_strs_dup(env);
	if (tmp_env == NULL)
	{
		ft_dprintf(2, "%s: export: %s\n", shell_name, strerror(ENOMEM));
		return (ENOMEM);
	}
	ft_strs_sort(tmp_env);
	i = 0;
	while (tmp_env[i])
	{
		if (tmp_env[i][0] != '_' || tmp_env[i][1] != '=')
			print_env_value(tmp_env[i]);
		i++;
	}
	ft_free_strs(tmp_env);
	return (0);
}
