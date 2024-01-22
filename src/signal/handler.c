/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:38:09 by psalame           #+#    #+#             */
/*   Updated: 2024/01/22 21:34:20 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <termios.h>

static void	signal_handler(int signal)
{
	ft_dprintf(1, "\033[%dC", rl_point + ft_strlen(rl_prompt));
	if (signal == 2)
	{
		ft_dprintf(1, "%c^C\n", 0);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	toggle_signal_handler(bool toggle)
{
	static struct sigaction	action;
	sigset_t			mask;
	struct termios		term_data;

	tcgetattr(0, &term_data);
	if (toggle)
	{
		term_data.c_lflag = term_data.c_lflag & (~ECHOCTL);
		tcsetattr(0, 0, &term_data);

		sigemptyset(&mask);
		sigaddset(&mask, SIGQUIT);
		action.sa_mask = mask;
		action.sa_flags = 0;
		action.sa_handler = &signal_handler;
		sigaction(SIGINT, &action, NULL);
		sigaction(SIGQUIT, &action, NULL);
	}
	else
	{
		action.sa_handler = SIG_IGN;
		sigaction(SIGINT, &action, NULL);
		sigaction(SIGQUIT, &action, NULL);
	}
}
