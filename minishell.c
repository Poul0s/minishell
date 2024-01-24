/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:18:21 by psalame           #+#    #+#             */
/*   Updated: 2024/01/24 23:56:37 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"
#include "autocompletion.h"

static void	print_syntax_error(t_syntax *syntax, t_sh_data *shell_data)
{
	// todo set last exec error at 2
	ft_dprintf(2, "%s: ", shell_data->exec_name);
	if (syntax->no_end)
		ft_dprintf(2, "syntax error: unexpected end of file\n");
	else
		ft_dprintf(2, "syntax error near unexpected token `%s'\n", syntax->token);
}

static void	execute_line(char *command_line_str, t_sh_data *shell_data)
{
	t_syntax			syntax_res;
	t_command_group		*command_line;
	int					last_cmd_code;
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
			last_cmd_code = execute_command_line(command_line, shell_data->exit_status, exec_data);
			shell_data->exit_status = last_cmd_code;
			free_command_line(command_line, false);
			free_command_line(NULL, true);
		}
		toggle_signal_handler(true);
	}
}

void	free_shell_data(t_sh_data *shell_data)
{
	free(shell_data->prompt);
	free(shell_data->hostname);
	ft_free_strs(shell_data->env);
	toggle_signal_handler(false);
	clear_history();
}

int	main(int ac, char **av, char **envp)
{
	char		*line_readed;
	t_sh_data	shell_data;

	(void) ac;
	rl_completion_entry_function = autocompletion;
	shell_data.exec_name = av[0];
	shell_data.env = ft_strs_dup(envp);
	shell_data.hostname = get_hostname();
	shell_data.exit_status = 0;
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
	free_shell_data(&shell_data);
	return (shell_data.exit_status);
}
