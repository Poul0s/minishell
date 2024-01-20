/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:07:20 by psalame           #+#    #+#             */
/*   Updated: 2024/01/20 15:49:36 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

static void	check_syntax_char(t_string_index *stri,
							t_syntax_parser *syntax,
							t_syntax *res)
{
	char	c;

	c = stri->str[stri->i];
	if (c == '\'' || c == '"')
	{
		syntax->has_content = true;
		if ((c == '\'' && syntax->current_token != '"')
			|| (c == '"' && syntax->current_token != '\''))
		{
			if (syntax->current_token == c)
				syntax->current_token = 0;
			else
				syntax->current_token = c;
		}
	}
	else if (syntax->current_token != '\'' && syntax->current_token != '"')
	{
		if (c == '&' || c == '|')
		{
			if (syntax->current_token != 0 || !syntax->has_content)
			{
				if (stri->str[stri->i + 1] == c)
					res->double_char_error = true;
				res->error = true;
				res->error_char = c;
			}
			else
			{
				syntax->current_token = c;
				if (stri->str[stri->i + 1] == c)
					stri->i++;
				syntax->has_content = false;
				syntax->current_token = c;
			}
		}
		else if (c == '(')
		{
			syntax->nb_parenthesis++;
			syntax->has_content = false;
		}
		else if (c == ')')
		{
			syntax->nb_parenthesis--;
			if (syntax->nb_parenthesis < 0)
			{
				res->error = true;
				res->error_char = ')';
			}
			else
				syntax->has_content = false;
		}
		else
			syntax->has_content = true;
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
	res.error = false;
	res.double_char_error = false;
	while (stri.str[stri.i])
	{
		str_i_skip_spaces(&stri);
		check_syntax_char(&stri, &syntax, &res);
		if (res.error)
			return (res);
		stri.i++;
	}
	if (syntax.nb_parenthesis > 0
		|| (syntax.current_token != 0 && !syntax.has_content)
		|| (syntax.current_token == '\'' || syntax.current_token == '"'))
	{
		res.error = true;
		res.error_char = EOF;
	}
	return (res);
}
