/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:38:09 by psalame           #+#    #+#             */
/*   Updated: 2024/02/23 23:09:28 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <termios.h>

extern int	g_exit_status;

static void	signal_handler(int signal)
{
	if (signal == 2)
	{
		g_exit_status = 130;
		ft_dprintf(1, "^C\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	ign(int signal)
{
	(void) signal;
}

void	toggle_signal_handler(bool toggle)
{
	struct termios		term_data;

	tcgetattr(0, &term_data);
	if (toggle)
	{
		term_data.c_lflag = term_data.c_lflag & (~ECHOCTL);
		tcsetattr(0, 0, &term_data);
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
	}
	else
	{
		term_data.c_lflag = term_data.c_lflag | ECHOCTL;
		tcsetattr(0, 0, &term_data);
		signal(SIGINT, ign);
		signal(SIGQUIT, ign);
	}
}
