/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:20:05 by psalame           #+#    #+#             */
/*   Updated: 2024/02/28 19:37:39 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_index_bonus.h"
#include "libft.h"

void	str_i_skip_spaces(t_string_index *command_line)
{
	while (command_line->str[command_line->i] == ' ')
		command_line->i++;
}

bool	is_var_arg_char_correct(t_string_index *cmd_line,
								int start,
								int current)
{
	if (cmd_line->str[current] == '_')
		return (true);
	else if (start != current && ft_isalnum(cmd_line->str[current]))
		return (true);
	else if (ft_isalpha(cmd_line->str[current]))
		return (true);
	return (false);
}
