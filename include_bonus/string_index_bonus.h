/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_index_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:13:11 by psalame           #+#    #+#             */
/*   Updated: 2024/02/28 19:33:09 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_INDEX_BONUS_H
# define STRING_INDEX_BONUS_H

# include <stddef.h>

typedef struct s_string_index
{
	char	*str;
	size_t	i;
}	t_string_index;

void	str_i_skip_spaces(t_string_index *command_line);

#endif
