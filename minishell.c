/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:18:21 by psalame           #+#    #+#             */
/*   Updated: 2024/01/16 18:48:06 by psalame          ###   ########.fr       */
/*   Updated: 2024/01/16 15:33:19 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include "autocompleion.h"

static void	execute_line(char *command_line_str, char **env)
{
	t_command_group	*command_line;

	command_line = parse_cmd_line(command_line_str, env);
	if (command_line)
		print_command_line(command_line, 0);
		// todo execute_command_line(command_line);
	else
		ft_free_strs(env);
	// todo free command_line
}

int	main(int ac, char **av, char **envp)
{
	char		*line_readed;
	t_sh_data	shell_data;

	(void) ac;
	(void) av;
	shell_data.hostname = get_hostname();
	refresh_prompt(&shell_data);
	line_readed = NULL;
	init_signal_handler();
	while (1)
	{
		rl_completion_entry_function = autocompletion;
		if (line_readed && *line_readed)
			add_history(line_readed);
		line_readed = readline(shell_data.prompt);
		if (!line_readed)
			break ;
		else
			execute_line(line_readed, ft_strs_dup(envp));
	}
	ft_dprintf(1, "exit\n");
	return (0);
}
