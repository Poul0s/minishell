/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:48:52 by psalame           #+#    #+#             */
/*   Updated: 2024/01/15 16:35:54 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*parse_commands(char *command_line)
{
	t_command	*first;
	t_command	*current_pipe;

	first = ft_calloc(1, sizeof(t_command));
	if (!first)
		return (first);
	current_pipe = first;
	return (first);
}

t_command_group	*parse_command_group(char *command_line)
{
	t_command_group	*res;

	res = ft_calloc(1, sizeof(t_command_group));
	if (!res)
		return (res);
	res->commands = parse_commands(command_line);
	return (res);
}

t_command_line	*parse_command_line(char *command_line)
{
	t_command_line	*res;

	res = ft_calloc(1, sizeof(t_command_line));
	if (!res)
		return (res);
	res->command_group = parse_command_group(command_line);
	return (res);
}
