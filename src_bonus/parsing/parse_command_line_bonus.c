/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:48:52 by psalame           #+#    #+#             */
/*   Updated: 2024/02/28 19:37:39 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_Int_bonus.h"
#include "minishell_bonus.h"

t_command_group	*parse_cmd_line(char *command_line, char ***env)
{
	t_string_index	str;

	str.str = command_line;
	str.i = 0;
	return (parse_command_grp(&str, env));
}
