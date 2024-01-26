/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:38:09 by psalame           #+#    #+#             */
/*   Updated: 2024/01/26 01:17:23 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <termios.h>

extern int	exit_status;

static void	signal_handler(int signal)
{
	ft_dprintf(1, "\033[%dC", rl_point + ft_strlen(rl_prompt));
	if (signal == 2)
	{
		exit_status = 130;
		ft_dprintf(1, "%c^C\n", 0);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	test(int signal)
{
	(void) signal;

	if (signal == SIGQUIT)
	{
		exit_status = 131;
		ft_dprintf(2, "Quit (core dumped)\n");
	}
	else
	{
		exit_status = 130;
		ft_dprintf(2, "\n");
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
		sigaddset(&mask, SIGINT);
		action.sa_mask = mask;
		action.sa_flags = SA_NODEFER;
		action.sa_handler = &signal_handler;
		sigaction(SIGINT, &action, NULL);
		sigaction(SIGQUIT, &action, NULL);
	}
	else
	{
		term_data.c_lflag = term_data.c_lflag | ECHOCTL;
		action.sa_flags = SA_NODEFER;
		tcsetattr(0, 0, &term_data);
		action.sa_handler = &test;
		sigaction(SIGINT, &action, NULL);
		sigaction(SIGQUIT, &action, NULL);
	}
}
