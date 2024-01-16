/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:18:21 by psalame           #+#    #+#             */
/*   Updated: 2024/01/16 14:49:57 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include <readline/readline.h>

char *autocompletion(const char *str, int status)
{
	static t_list *head = NULL;
	char *word;

	if (!head)
	{
		word = wich_word();
		if (!word)
			return (NULL);
		head = find_match_cmd(word);
		free(word);
	}
	(void)str;
	if (status)
		head = head->next;
	if (!head)
		return(NULL);
	return ((char *)head->content);
}

static void	execute_line(char *command_line_str)
{
	t_command_group	*command_line;

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
	line_readed = NULL;
	while (1)
	{
		rl_completion_entry_function = autocompletion;
		if (line_readed && *line_readed)
			add_history(line_readed);
		line_readed = readline(shell_data.prompt);
		if (!line_readed)
			break ;
		else
			execute_line(line_readed);
	}
	ft_dprintf(0, "exit\n");
	return (0);
}
