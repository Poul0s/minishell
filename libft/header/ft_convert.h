/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 22:03:37 by psalame           #+#    #+#             */
/*   Updated: 2024/01/13 11:02:00 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONVERT_H
# define FT_CONVERT_H
# include "libft.h"

int				ft_tolower(int c);
int				ft_toupper(int c);
int				ft_atoi(const char *nptr);
char			*ft_itoa(int n);
char			*ft_ultoa_base(unsigned long nb, const char *base);
unsigned int	ft_abs(int value);

#endif
