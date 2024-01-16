/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:18:21 by psalame           #+#    #+#             */
/*   Updated: 2024/01/16 03:08:41 by babonnet         ###   ########.fr       */
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
