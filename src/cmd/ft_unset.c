/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 23:49:31 by psalame           #+#    #+#             */
/*   Updated: 2024/02/26 14:46:06 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_command *command)
{
	size_t	i;
	char	***env;

	env = command->env;
	i = 1;
	while (command->arguments[i])
	{
		*env = del_env_var(*env, command->arguments[i]);
		i++;
	}
	return (0);
}
