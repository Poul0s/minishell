/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:07:20 by psalame           #+#    #+#             */
/*   Updated: 2024/01/29 16:38:03 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

void	check_syntax_char(t_string_index *stri,
			t_syntax_parser *syntax,
			t_syntax *res);

static void	check_syntax_end(t_syntax *res, t_syntax_parser *syntax)
{
	if (syntax->nb_parenthesis > 0
		|| (syntax->current_token != 0 && !syntax->has_content)
		|| (syntax->current_token == '\'' || syntax->current_token == '"'))
	{
		res->error = true;
		if (syntax->current_token == '>' || syntax->current_token == '<')
			res->token = ft_strdup("newline");
		else
			res->no_end = true;
	}
}

t_syntax	check_syntax(char *command_line)
{
	t_string_index	stri;
	t_syntax_parser	syntax;
	t_syntax		res;

	stri.str = command_line;
	stri.i = 0;
	ft_bzero(&syntax, sizeof(t_syntax_parser));
	ft_bzero(&res, sizeof(t_syntax));
	syntax.current_token = 1;
	str_i_skip_spaces(&stri);
	while (stri.str[stri.i])
	{
		check_syntax_char(&stri, &syntax, &res);
		if (res.error)
			return (res);
		stri.i++;
		str_i_skip_spaces(&stri);
	}
	check_syntax_end(&res, &syntax);
	return (res);
}
