/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_index.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:13:11 by psalame           #+#    #+#             */
/*   Updated: 2024/01/20 15:47:30 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_INDEX_H
# define STRING_INDEX_H

# include <stddef.h>

typedef struct s_string_index
{
	char	*str;
	size_t	i;
}	t_string_index;

void	str_i_skip_spaces(t_string_index *command_line);

#endif