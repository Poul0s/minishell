/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:48:52 by psalame           #+#    #+#             */
/*   Updated: 2024/01/22 14:21:12 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_Int.h"
#include "minishell.h"

t_command_group	*parse_cmd_line(char *command_line, t_env_tree *env)
{
	t_string_index	str;

	str.str = command_line;
	str.i = 0;
	return (parse_command_grp(&str, env));
}
