/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:18:21 by psalame           #+#    #+#             */
/*   Updated: 2024/01/15 14:55:45 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char		*line_readed;
	t_sh_data	shell_data;

	shell_data.hostname = get_hostname();
	refresh_prompt(&shell_data);
	line_readed = readline(shell_data.prompt);
	while (line_readed != NULL)
	{
		line_readed = readline(shell_data.prompt);
	}
	return (0);
}