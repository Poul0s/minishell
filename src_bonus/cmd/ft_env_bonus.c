/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:31:04 by babonnet          #+#    #+#             */
/*   Updated: 2024/02/28 19:37:38 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell_bonus.h"

int	ft_env(t_command *command)
{
	char	**env;

	env = *(command->env);
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
