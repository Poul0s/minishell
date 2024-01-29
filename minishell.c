/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:18:21 by psalame           #+#    #+#             */
/*   Updated: 2024/01/29 16:04:03 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"
#include "autocompletion.h"

int	g_exit_status;

static void	print_syntax_error(t_syntax *syntax, t_sh_data *shell_data)
{
	ft_dprintf(2, "%s: ", shell_data->exec_name);
	if (syntax->no_end)
		ft_dprintf(2, "syntax error: unexpected end of file\n");
	else
		ft_dprintf(2, "syntax error near unexpected token `%s'\n", syntax->token);
	g_exit_status = 2;
}

static void	execute_line(char *command_line_str, t_sh_data *shell_data)
{
	t_syntax			syntax_res;
	t_command_group		*command_line;
	int					res_command_line;
	t_execution_data	exec_data;

	if (command_line_str[0] == 0)
		return ;
	syntax_res = check_syntax(command_line_str);
	if (syntax_res.error)
		print_syntax_error(&syntax_res, shell_data);
	else
	{
		command_line = parse_cmd_line(command_line_str, &(shell_data->env));
		toggle_signal_handler(false);
		if (command_line)
		{
			exec_data.forked = false;
			exec_data.base_command_line = command_line;
			exec_data.shell_data = shell_data;
			res_command_line = execute_command_line(command_line, exec_data);
			if (res_command_line != -1)
				g_exit_status = res_command_line;
			free_command_line(command_line, false);
			free_command_line(NULL, true);
		}
		toggle_signal_handler(true);
	}
}

void	free_shell_data(t_sh_data *shell_data, bool disable_signal)
{
	free(shell_data->prompt);
	free(shell_data->hostname);
	free(shell_data->exec_name);
	ft_free_strs(shell_data->env);
	if (disable_signal)
		toggle_signal_handler(false);
	clear_history();
}

int	main(int ac, char **av, char **envp)
{
	char		*line_readed;
	t_sh_data	shell_data;

	(void) ac;
	rl_completion_entry_function = autocompletion;
	shell_data.exec_name = get_exec_name(av[0]);
	shell_data.env = ft_strs_dup(envp);
	shell_data.hostname = get_hostname();
	g_exit_status = 0;
	shell_data.prompt = NULL;
	refresh_prompt(&shell_data);
	line_readed = NULL;
	toggle_signal_handler(true);
	while (1)
	{
		if (line_readed && *line_readed)
			add_history(line_readed);
		line_readed = readline(shell_data.prompt);
		if (!line_readed)
			break ;
		else
			execute_line(line_readed, &shell_data);
		refresh_prompt(&shell_data);
	}
	ft_dprintf(1, "exit\n");
	free_shell_data(&shell_data, true);
	return (g_exit_status);
}
