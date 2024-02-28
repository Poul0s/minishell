/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_manager_bonus.h                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:10:11 by psalame           #+#    #+#             */
/*   Updated: 2024/02/28 19:34:16 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_MANAGER_BONUS_H
# define ENVIRONMENT_MANAGER_BONUS_H

# include "libft.h"

bool	has_env_var(char **env, char *key);
char	*get_env_var(char **env, char *key);
char	**del_env_var(char **env, char *key);
char	**edit_env_var(char **env, char *key, char *new_value);

#endif
