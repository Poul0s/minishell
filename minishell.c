/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:18:21 by psalame           #+#    #+#             */
/*   Updated: 2024/01/15 20:25:04 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_line(char *command_line_str)
{
	t_command_line	*command_line;

	// todo history fct
	command_line = parse_cmd_line(command_line_str);
	if (command_line)
		print_command_line(command_line, 0);
		// todo execute_command_line(command_line);
	// todo free command_line
}

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
