/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_char_checker.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:30:24 by psalame           #+#    #+#             */
/*   Updated: 2024/02/28 19:37:39 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax_bonus.h"

static void	check_operator_syntax(t_string_index *stri,
								t_syntax_parser *syntax,
								t_syntax *res)
{
	char	c;

	c = stri->str[stri->i];
	if (syntax->current_token != 0 && !syntax->has_content)
	{
		res->error = true;
		if (stri->str[stri->i + 1] == c)
			res->token = token_to_str(c, 2);
		else
			res->token = token_to_str(c, 1);
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

static void	check_fileredirection_syntax(t_string_index *stri,
							t_syntax_parser *syntax,
							t_syntax *res)
{
	char	c;
	short	token_size;

	c = stri->str[stri->i];
	if ((syntax->current_token == '>' || syntax->current_token == '<')
		&& syntax->has_content != true)
	{
		res->error = true;
		token_size = 1;
		while (stri->str[stri->i + token_size] == c && token_size < 3)
			token_size++;
		res->token = token_to_str(c, token_size);
	}
	else
	{
		if (stri->str[stri->i + 1] == c)
			stri->i++;
		syntax->has_content = false;
		syntax->current_token = c;
	}
}

static void	check_parenthesis_syntax(t_string_index *stri,
									t_syntax_parser *syntax,
									t_syntax *res)
{
	char	c;

	c = stri->str[stri->i];
	if (c == '(')
	{
		syntax->nb_parenthesis++;
		syntax->has_content = false;
	}
	else
	{
		syntax->nb_parenthesis--;
		if (syntax->nb_parenthesis < 0 || !syntax->has_content)
		{
			res->error = true;
			res->token = token_to_str(')', 1);
		}
		else
		{
			syntax->has_content = true;
			syntax->current_token = 0;
		}
	}
}

static void	check_syntax_quote(t_string_index *stri,
							t_syntax_parser *syntax)
{
	char	c;

	c = stri->str[stri->i];
	syntax->has_content = true;
	if ((c == '\'' && syntax->current_token != '"')
		|| (c == '"' && syntax->current_token != '\''))
	{
		if (syntax->current_token == c)
			syntax->current_token = 1;
		else
			syntax->current_token = c;
	}
}

void	check_syntax_char(t_string_index *stri,
							t_syntax_parser *syntax,
							t_syntax *res)
{
	char	c;

	c = stri->str[stri->i];
	if (c == '\'' || c == '"')
		check_syntax_quote(stri, syntax);
	else if (syntax->current_token != '\'' && syntax->current_token != '"')
	{
		if (c == '&' || c == '|')
			check_operator_syntax(stri, syntax, res);
		else if (c == '(' || c == ')')
			check_parenthesis_syntax(stri, syntax, res);
		else if (c == '>' || c == '<')
			check_fileredirection_syntax(stri, syntax, res);
		else
		{
			if (syntax->current_token)
				syntax->has_content = true;
			else
			{
				res->error = true;
				res->token = get_unexpected_token(stri);
			}
		}
	}
}
