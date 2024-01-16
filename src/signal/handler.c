/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:38:09 by psalame           #+#    #+#             */
/*   Updated: 2024/01/16 17:27:54 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

static void	signal_handler(int signal, siginfo_t *info, void *old_info)
{
	(void) info;
	(void) old_info;
	if (signal == 2)
	{
		ft_dprintf(1, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_signal_handler(void)
{
	struct sigaction	action;
	sigset_t			mask;

	sigemptyset(&mask);
	action.sa_mask = mask;
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = &signal_handler;
	sigaction(-1, &action, NULL);
	sigaction(2, &action, NULL);
}
