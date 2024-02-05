/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:31:04 by babonnet          #+#    #+#             */
/*   Updated: 2024/02/05 18:28:29 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_env(char **env)
{
	if (!env)
		return (1);
	while (*env)
	{
		if (ft_strchr(*env, '=') != NULL)
			ft_printf("%s\n", *env);
		env++;
	}
	return (0);
}
