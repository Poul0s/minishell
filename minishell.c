/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:18:21 by psalame           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/01/16 03:08:41 by babonnet         ###   ########.fr       */
=======
/*   Updated: 2024/01/15 20:25:04 by psalame          ###   ########.fr       */
>>>>>>> 31c5ea3a28ab17f8e1874406f028015fe3907887
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

char *autocompletion(const char *str, int status)
{
	static t_list *head = NULL;

	if (!head)
		head = find_match_cmd(rl_line_buffer);
	(void)str;
	if (status)
		head = head->next;
	if (!head)
		return(NULL);
	return ((char *)head->content);
}

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
		rl_completion_entry_function = autocompletion;
		if (line_readed && *line_readed)
			add_history (line_readed);
		line_readed = readline(shell_data.prompt);
	}
	return (0);
}
