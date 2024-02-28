/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:38:09 by psalame           #+#    #+#             */
/*   Updated: 2024/02/28 19:46:28 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include <signal.h>
#include <termios.h>

extern int	g_exit_status;

static void	signal_handler(int signal)
{
	if (signal == 2)
	{
		g_exit_status = 130;
		ft_dprintf(2, "^C\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	ign(int signal)
{
	(void) signal;
}

void	toggle_signal_handler(bool toggle_handler, bool toggle_termios_print)
{
	struct termios		term_data;
	void				(*fct_handler)(int);

	if (toggle_handler)
		fct_handler = &signal_handler;
	else
		fct_handler = &ign;
	signal(SIGINT, fct_handler);
	signal(SIGQUIT, fct_handler);
	tcgetattr(0, &term_data);
	if (!toggle_termios_print)
	{
		term_data.c_lflag = term_data.c_lflag & (~ECHOCTL);
		tcsetattr(0, 0, &term_data);
	}
	else
	{
		term_data.c_lflag = term_data.c_lflag | ECHOCTL;
		tcsetattr(0, 0, &term_data);
	}
}
