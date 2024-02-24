/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:18:21 by psalame           #+#    #+#             */
/*   Updated: 2024/02/24 13:21:05 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "autocompletion.h"
#include "here_doc.h"

int	g_exit_status;

static void	print_syntax_error(t_syntax *syntax, t_sh_data *shell_data)
{
	char	*token;

	ft_dprintf(2, "%s: ", shell_data->exec_name);
	if (syntax->no_end)
		ft_dprintf(2, "syntax error: unexpected end of file\n");
	else
	{
		token = syntax->token;
		ft_dprintf(2, "syntax error near unexpected token `%s'\n", token);
	}
	g_exit_status = 2;
}

static void	execute_line(char *command_line_str, t_sh_data *shell_data)
{
	t_syntax			syntax_res;
	t_command_group		*command_line;
	int					res_command_line;
	t_execution_data	exec_data;
	int					error_here_doc;

	syntax_res = check_syntax(command_line_str);
	if (syntax_res.error)
		print_syntax_error(&syntax_res, shell_data);
	else
	{
		command_line = parse_cmd_line(command_line_str, &(shell_data->env));
		toggle_signal_handler(false);
		if (command_line)
		{
			error_here_doc = 0;
			manage_here_doc(command_line,&error_here_doc);
			exec_data.forked = false;
			exec_data.base_command_line = command_line;
			exec_data.shell_data = shell_data;
			if (!error_here_doc)
				res_command_line = execute_command_line(command_line, exec_data);
			if (!error_here_doc && res_command_line != -1)
				g_exit_status = res_command_line;
			free_command_line(command_line, false);
			free_command_line(NULL, true);
		}
		toggle_signal_handler(true);
	}
}

static void	init_shell_data(t_sh_data *shell_data, char **av, char **envp)
{
	int		shell_lvl;
	char	*shell_lvl_str;

	shell_data->exec_name = get_exec_name(av[0]);
	shell_data->env = ft_strs_dup(envp);
	shell_lvl_str = get_env_var(shell_data->env, "SHLVL");
	if (shell_lvl_str)
		shell_lvl = ft_atoi(get_env_var(shell_data->env, "SHLVL"));
	else
		shell_lvl = 0;
	shell_lvl++;
	if (shell_lvl < 0)
		shell_lvl = 0;
	shell_lvl_str = ft_itoa(shell_lvl);
	shell_data->env = edit_env_var(shell_data->env, "SHLVL", shell_lvl_str);
	free(shell_lvl_str);
	shell_data->hostname = get_hostname();
	g_exit_status = 0;
	shell_data->prompt = NULL;
	refresh_prompt(shell_data);
	toggle_signal_handler(true);
}

static bool	is_str_empty(char *str)
{
	while (*str)
	{
		if (*str != ' ')
			return (false);
		str++;
	}
	return (true);
}

int	main(int ac, char **av, char **envp)
{
	char		*line_readed;
	t_sh_data	shell_data;

	(void) ac;
	rl_catch_signals = 0;
	rl_completion_entry_function = autocompletion;
	init_shell_data(&shell_data, av, envp);
	line_readed = NULL;
	while (1)
	{
		if (line_readed && *line_readed)
			add_history(line_readed);
		line_readed = readline(shell_data.prompt);
		if (!line_readed)
			break ;
		else if (!is_str_empty(line_readed))
			execute_line(line_readed, &shell_data);
		refresh_prompt(&shell_data);
	}
	ft_dprintf(1, "exit\n");
	free_shell_data(&shell_data, true);
	return (g_exit_status);
}
