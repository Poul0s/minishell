/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 22:04:33 by psalame           #+#    #+#             */
/*   Updated: 2024/01/13 13:47:58 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINT_H
# define FT_PRINT_H
# include "libft.h"

ssize_t	ft_putchar_fd(char c, int fd);
void	ft_putchar_rep(char c, int rep, int fd);
ssize_t	ft_putstr_fd(char *s, int fd);
ssize_t	ft_putendl_fd(char *s, int fd);
ssize_t	ft_putnbr_fd(int n, int fd);
int		ft_printf(const char *str, ...);
int		ft_dprintf(int fd, const char *str, ...);
ssize_t	ft_putptr_fd(void *ptr, int fd);
ssize_t	ft_putunbr_fd(unsigned int nb, int fd);
ssize_t	ft_putxnbr_fd(unsigned int nb, short maj, int fd);

#endif
