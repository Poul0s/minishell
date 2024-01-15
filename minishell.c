/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:18:21 by psalame           #+#    #+#             */
/*   Updated: 2024/01/15 14:22:28 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	refresh_prompt(t_sh_data *shell_data)
{
	char	*username;
	char	*pwd;

	username = getenv("USER");
	
}

int	main(void)
{
	char		*line_readed;
	t_sh_data	shell_data;

	shell_data.hostname = get_hostname();
	init_prompt(&shell_data);
	line_readed = readline(shell_data.prompt);
	while (line_readed != NULL)
	{
		line_readed = readline(shell_data.prompt);
	}
	return (0);
}