/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:38:09 by psalame           #+#    #+#             */
/*   Updated: 2024/01/17 13:51:54 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <termios.h>

static void	signal_handler(int signal, siginfo_t *info, void *old_info)
{

	struct termios	term_data;

	(void) info;
	(void) old_info;
	if (signal == 2)
	{
		ft_dprintf(1, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		(void) term_data;
		// not working first time + remove ^C print...
		// tcgetattr(0, &term_data);
		// term_data.c_lflag = term_data.c_lflag & (~ECHOCTL);
		// tcsetattr(0, 0, &term_data);
	}
}

void	init_signal_handler(void)
{
	struct sigaction	action;
	sigset_t			mask;

	sigemptyset(&mask);
	sigaddset(&mask, SIGQUIT);
	action.sa_mask = mask;
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = &signal_handler;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
}
