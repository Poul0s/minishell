/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:18:21 by psalame           #+#    #+#             */
/*   Updated: 2024/02/28 17:59:25 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocompletion.h"
#include "environment_manager.h"
#include "here_doc.h"
#include "minishell.h"

int			g_exit_status;

static void	execute_line_res(t_command_group *cmd_line, t_sh_data *shell_data)
{
	int					error_here_doc;
	t_execution_data	exec_data;
	int					res_cmd_line;

	error_here_doc = 0;
	exec_data.forked = false;
	exec_data.base_command_line = cmd_line;
	exec_data.shell_data = shell_data;
	manage_here_doc(cmd_line, &error_here_doc, exec_data);
	if (!error_here_doc)
		res_cmd_line = execute_command_line(cmd_line, exec_data);
	if (!error_here_doc && res_cmd_line != -1)
		g_exit_status = res_cmd_line;
	close_all_fd(cmd_line);
	free_command_line(cmd_line, false);
	free_command_line(NULL, true);
}

static void	execute_line(char *cmd_line_str, t_sh_data *shell_data)
{
	t_syntax		syntax_res;
	t_command_group	*cmd_line;

	syntax_res = check_syntax(cmd_line_str);
	if (syntax_res.error)
		print_syntax_error(&syntax_res, shell_data);
	else
	{
		cmd_line = parse_cmd_line(cmd_line_str, &(shell_data->env));
		toggle_signal_handler(false, true);
		if (cmd_line)
			execute_line_res(cmd_line, shell_data);
		toggle_signal_handler(true, false);
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
	shell_data->env = edit_env_var(shell_data->env, "OLDPWD",
			get_env_var(shell_data->env, "PWD"));
	free(shell_lvl_str);
	shell_data->hostname = get_hostname();
	g_exit_status = 0;
	shell_data->prompt = NULL;
	refresh_prompt(shell_data);
	toggle_signal_handler(true, false);
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

	(void)ac;
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
