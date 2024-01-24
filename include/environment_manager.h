/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_manager.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:10:11 by psalame           #+#    #+#             */
/*   Updated: 2024/01/24 18:14:32 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_MANAGER_H
# define ENVIRONMENT_MANAGER_H

# include "libft.h"

bool	has_env_var(char **env, char *key);
char	*get_env_var(char **env, char *key);
char	**del_env_var(char **env, char *key);
char	**edit_env_var(char **env, char *key, char *new_value);

#endif