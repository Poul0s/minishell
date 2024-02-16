/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 21:59:42 by psalame           #+#    #+#             */
/*   Updated: 2024/02/15 23:46:38 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_H
# define FT_STRING_H
# include "libft.h"

size_t	ft_strlen(char const *str);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(char const	*s1, char const *s2);
char	*ft_strfjoin(char *s1, char *s2);
char	*ft_strfjoin_chr(char *s1, char c);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strdup(const char *s);
void	ft_free_strs(char **strs);
size_t	ft_strs_len(char **strs);
char	**ft_strs_dup(char **src);
char	*ft_str_insert(char *src, char *str, size_t pos);
char	**ft_strs_insert_str(char **src, char *new_elem, size_t pos);

#endif
