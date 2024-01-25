/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 23:58:47 by psalame           #+#    #+#             */
/*   Updated: 2024/01/25 13:09:23 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// exit with no argument : exit with last exit code
// exit with non-numeric : exit, 2, write "bash: exit: {arg}: numeric argument required" 
// exit with multiple argument : no exit, return 1, write "bash: exit: too many arguments" 
// exit normal: AtoUNSIGNEDCHAR argument and exit with it

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

int	ft_exit(t_command *command, int last_exit_status)
{
	unsigned char	exit_code;

	if (command->arguments[1] == NULL)
		exit_code = last_exit_status;
	else if (!is_str_num(command->arguments[1]))
	{
		ft_dprintf(2, "minishell: exit: %s: numeric argument required\n", command->arguments[1]);
		exit_code = 2;
	}
	else if (command->arguments[2] != NULL)
	{
		ft_dprintf(2, "minishell: exit: too many arguments\n");
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
