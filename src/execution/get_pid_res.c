/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pid_res.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:17:58 by psalame           #+#    #+#             */
/*   Updated: 2024/02/27 16:18:25 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>
#include <sys/wait.h>

int	get_pid_res(int pid)
{
	int	pid_res;

	pid_res = 0;
	waitpid(pid, &pid_res, 0);
	if (!WIFEXITED(pid_res))
	{
		if ((WCOREDUMP(pid_res)))
		{
			ft_dprintf(2, "Quit (core dumped)\n");
			return (131);
		}
		else
		{
			ft_dprintf(2, "\n");
			return (130);
		}
	}
	return (WEXITSTATUS(pid_res));
}
