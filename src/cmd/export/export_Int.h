/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_Int.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:54:01 by psalame           #+#    #+#             */
/*   Updated: 2024/02/02 15:24:48 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_INT_H
# define EXPORT_INT_H

# include "environment_manager.h"
# include "libft.h"
# include <errno.h>
# include <string.h>

int		is_key_good_format(char *str);
int		print_env_sorted(char **env, char *shell_name);
void	print_invalid_identifier(char *id, char *program_name);
int		parse_env_var_data(char *argument, char ***env, char *shell_name);

#endif