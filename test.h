/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 01:43:53 by babonnet          #+#    #+#             */
/*   Updated: 2024/01/18 01:43:59 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# ifndef __KM_VA_ARGS__
#  define __KM_VA_ARGS__

typedef char	*km_va_list;
#  define km_va_start(ap, parmn) (void)((ap) = (char *)(&(parmn) + 1))
#  define km_va_arg(ap, type) (((type *)((ap) = ((ap) + sizeof(type))))[-1])
#  define km_va_end(ap) (void)((ap) = 0)

# endif

#endif
