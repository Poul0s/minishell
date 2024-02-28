/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 20:05:06 by psalame           #+#    #+#             */
/*   Updated: 2024/02/28 16:38:38 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "here_doc.h"
#include "signal.h"

extern int	g_exit_status;

static void	toggle_hd_garbage(t_hd_reader_data *_hd_data)
{
	static t_hd_reader_data	*hd_data = NULL;

	if (_hd_data)
		hd_data = _hd_data;
	else
	{
		free(hd_data->file_name);
		close_all_fd(hd_data->exec_data.base_command_line);
		if (hd_data->fd > 0)
			close(hd_data->fd);
		free_command_line(hd_data->exec_data.base_command_line, false);
		free_command_line(NULL, true);
		free_shell_data(hd_data->exec_data.shell_data, false);
	}
}

static void	hd_signal_handler(int signal)
{
	(void) signal;
	toggle_hd_garbage(NULL);
	ft_printf("^C\n");
	exit(130);
}

static void	heredoc_reader(t_hd_reader_data *hd_data)
{
	char	*line_read;

	while (1)
	{
		if (hd_data->fd != -1 && access(hd_data->file_name, W_OK) == -1)
		{
			ft_dprintf(2,
				"minishell: here_doc temporary file has ben deleted\n");
			toggle_hd_garbage(NULL);
			exit(1);
		}
		line_read = readline("> ");
		if (!line_read)
		{
			ft_dprintf(2, "minishell: warning: here-document ");
			ft_dprintf(2, "delimited by end-of-file (wanted `%s')\n",
				hd_data->delimiter);
			break ;
		}
		if (!ft_strncmp(line_read, hd_data->delimiter, hd_data->delimiter_len))
			break ;
		if (hd_data->fd != -1)
			ft_putendl_fd(line_read, hd_data->fd);
	}
}

void	start_heredoc_process(char *delimiter,
							int fd,
							char *file_name,
							t_execution_data exec_data)
{
	t_hd_reader_data	hd_data;

	hd_data.delimiter = delimiter;
	hd_data.delimiter_len = ft_strlen(delimiter) + 1;
	hd_data.fd = fd;
	hd_data.file_name = file_name;
	hd_data.exec_data = exec_data;
	toggle_hd_garbage(&hd_data);
	signal(SIGINT, &hd_signal_handler);
	heredoc_reader(&hd_data);
	toggle_hd_garbage(NULL);
	exit(0);
}

int	read_here_doc(char *delimiter,
				int fd,
				char *file_name,
				t_execution_data exec_data)
{
	int		pid;
	int		pid_res;

	if (!delimiter)
		return (0);
	pid = fork();
	if (pid == 0)
		start_heredoc_process(delimiter, fd, file_name, exec_data);
	else if (pid == -1)
		return (1);
	waitpid(pid, &pid_res, 0);
	if (WIFEXITED(pid_res))
		g_exit_status = WEXITSTATUS(pid_res);
	return (WIFEXITED(pid_res) != true || WEXITSTATUS(pid_res) != 0);
}
