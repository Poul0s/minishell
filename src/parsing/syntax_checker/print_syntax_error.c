/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:34:57 by psalame           #+#    #+#             */
/*   Updated: 2024/02/28 14:21:03 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	print_syntax_error(t_syntax *syntax, void *shell_data)
{
	char	*token;

	ft_dprintf(2, "%s: ", ((t_sh_data *) shell_data)->exec_name);
	if (syntax->no_end)
		ft_dprintf(2, "syntax error: unexpected end of file\n");
	else
	{
		token = syntax->token;
		ft_dprintf(2, "syntax error near unexpected token `%s'\n", token);
		free(token);
	}
	g_exit_status = 2;
}
