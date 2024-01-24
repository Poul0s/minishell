/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 21:03:09 by psalame           #+#    #+#             */
/*   Updated: 2024/01/24 21:05:48 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_manager.h"

int	ft_export(char **arguments, char **env)
{
	edit_env_var(env, arguments[1], arguments[2]);
	return (0);
}
