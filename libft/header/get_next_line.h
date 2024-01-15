/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:00:19 by psalame           #+#    #+#             */
/*   Updated: 2023/11/25 02:19:56 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft.h"

char	*get_next_line(int fd);
void	close_next_line(int fd);
ssize_t	ft_read_to_cstr(int fd, char *buffer);

#endif
