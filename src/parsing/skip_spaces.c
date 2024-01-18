/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_spaces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:20:05 by psalame           #+#    #+#             */
/*   Updated: 2024/01/18 14:20:33 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_Int.h"

void	str_i_skip_spaces(t_string_index *command_line)
{
	while (command_line->str[command_line->i] == ' ')
		command_line->i++;
}
