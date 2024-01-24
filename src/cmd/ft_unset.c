/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 23:49:31 by psalame           #+#    #+#             */
/*   Updated: 2024/01/24 23:51:46 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_manager.h"

int	ft_unset(char **arguments, char ***env)
{
	size_t	i;

	i = 1;
	while (arguments[i])
	{
		*env = del_env_var(*env, arguments[i]);
		i++;
	}
	return (0);
}
