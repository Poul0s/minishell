/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:07:43 by psalame           #+#    #+#             */
/*   Updated: 2024/02/26 21:39:09 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H
# define SYNTAX_H
# include "libft.h"
# include "string_index.h"

# ifndef EOF
#  define EOF -1
# endif

typedef struct s_syntax_parser
{
	char	current_token;
	int		nb_parenthesis;
	bool	has_content;
}			t_syntax_parser;

typedef struct s_syntax
{
	bool	error;
	bool	no_end;
	char	*token;
}			t_syntax;

char		*token_to_str(char c, int token_size);
char		*get_unexpected_token(t_string_index *stri);
t_syntax	check_syntax(char *command_line);
void		print_syntax_error(t_syntax *syntax, void *shell_data);

#endif
