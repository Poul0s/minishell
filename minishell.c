/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:18:21 by psalame           #+#    #+#             */
/*   Updated: 2024/01/20 18:44:06 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"
#include "autocompletion.h"

static void	print_syntax_error(t_syntax *syntax, t_sh_data *shell_data)
{
	// todo set last exec error at 2
	ft_dprintf(2, "%s: ", shell_data->exec_name);
	if (syntax->error_char == EOF)
		ft_dprintf(2, "syntax error: unexpected end of file\n");
	else
	{
		ft_dprintf(2, "syntax error near unexpected token `");
		ft_putchar_rep(syntax->error_char, 1 + syntax->double_char_error, 2);
		ft_dprintf(2, "'\n");
	}
}

static void	execute_line(char *command_line_str, t_sh_data *shell_data)
{
	t_syntax		syntax_res;
	t_command_group	*command_line;

	syntax_res = check_syntax(command_line_str);
	if (syntax_res.error && false)
		print_syntax_error(&syntax_res, shell_data);
	else
	{
		command_line = parse_cmd_line(command_line_str, shell_data->env);
		if (command_line)
		{
			execute_command_line(command_line);
			// print_command_line(command_line, 0);
		}
		// todo free command_line
	}
}

int	main(int ac, char **av, char **envp)
{
	char		*line_readed;
	t_sh_data	shell_data;

	(void) ac;
	(void) av;
	rl_completion_entry_function = autocompletion;
	shell_data.exec_name = av[0];
	shell_data.env = create_env_tree(NULL, envp);
	shell_data.hostname = get_hostname();
	refresh_prompt(&shell_data);
	line_readed = NULL;
	init_signal_handler();
	while (1)
	{
		if (line_readed && *line_readed)
			add_history(line_readed);
		line_readed = readline(shell_data.prompt);
		if (!line_readed)
			break ;
		else
			execute_line(line_readed, &shell_data);
	}
	ft_dprintf(1, "exit\n");
	return (0);
}
