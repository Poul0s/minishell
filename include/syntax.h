/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:07:43 by psalame           #+#    #+#             */
/*   Updated: 2024/01/20 15:51:54 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H
# define SYNTAX_H
# include "libft.h"
# include "string_index.h"
# define EOF -1

typedef struct s_syntax_parser
{
	char	current_token;
	int		nb_parenthesis;
	bool	has_content;
}	t_syntax_parser;

typedef struct s_syntax
{
	bool	error;
	char	error_char;
	bool	double_char_error;
}	t_syntax;

t_syntax	check_syntax(char *command_line);

#endif
