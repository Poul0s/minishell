/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:41:11 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/24 17:03:03 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_home_path(void)
{
	char	*path;
	char	**tmp;

	tmp = ft_split(getenv("PATH"), ':');
	if (!tmp)
		return (NULL);
	path = ft_strdup(tmp[0]);
	ft_free_strs(tmp);
	return (path);
}

int	ft_cd(const char **path)
{
	char	*final_path;

	if (!path)
		return (127);
	else if (path[0] && !path[1])
		final_path = get_home_path();
	else if (path[2])
	{
		ft_dprintf(2, "minishell: cd: too many arguments\n");
		return (1);
	}
	final_path = ft_strdup(path[1]);
	if (chdir(final_path) == -1)
	{
		ft_dprintf(2, "minishell: cd: %s: No such file or directory\n",
			final_path);
		free(final_path);
		return (1);
	}
	free(final_path);
	return (0);
}
