/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 23:58:47 by psalame           #+#    #+#             */
/*   Updated: 2024/02/28 19:37:38 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#define ERR_NUM_ARG_REQ "%s: exit: %s: numeric argument required\n"
#define ERR_TOO_MANY_ARG "%s: exit: too many arguments\n"

extern int	g_exit_status;

bool	is_str_num(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

static unsigned char	ft_atouc(char *str)
{
	unsigned int	number;
	int				sign;
	size_t			i;

	number = 0;
	sign = 1;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (ft_isdigit(str[i]))
	{
		number = number * 10 + str[i] - '0';
		i++;
	}
	return (number * sign);
}

int	ft_exit(t_command *command)
{
	unsigned char	exit_code;
	char			*exec_name;

	exec_name = command->exec_data.shell_data->exec_name;
	if (command->arguments[1] == NULL)
		exit_code = g_exit_status;
	else if (!is_str_num(command->arguments[1]))
	{
		ft_dprintf(2, ERR_NUM_ARG_REQ, exec_name, command->arguments[1]);
		exit_code = 2;
	}
	else if (command->arguments[2] != NULL)
	{
		ft_dprintf(2, ERR_TOO_MANY_ARG, exec_name);
		return (1);
	}
	else
		exit_code = ft_atouc(command->arguments[1]);
	free(command->exec_data.pid);
	free_shell_data(command->exec_data.shell_data, command->exec_data.forked);
	free_command_line(command->exec_data.base_command_line, false);
	free_command_line(NULL, true);
	exit(exit_code);
}
