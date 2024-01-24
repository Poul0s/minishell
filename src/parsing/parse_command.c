/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:36:03 by psalame           #+#    #+#             */
/*   Updated: 2024/01/24 18:04:03 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_Int.h"
#include "minishell.h"

static void	convert_command_arguments(t_command *command, t_list *arguments)
{
	size_t	i;

	command->arguments = malloc((ft_lstsize(arguments) + 1) * sizeof(char *));
	if (!command->arguments)
		return ;
	i = 0;
	while (arguments)
	{
		command->arguments[i++] = arguments->content;
		arguments = arguments->next;
	}
	command->arguments[i] = NULL;
}

static void	parse_command_data(t_string_index *command_line,
						t_command *command)
{
	t_list	*arguments;
	char	*argument;

	while (command_line->str[command_line->i] == ' ')
		command_line->i++;
	arguments = NULL;
	argument = parse_argument(command_line, command, &arguments);
	while (argument)
	{
		ft_lstadd_back(&arguments, ft_lstnew_fallback(argument, &free));
		argument = parse_argument(command_line, command, &arguments);
	}
	if (ft_lstsize(arguments) == 0)
		return ;
	convert_command_arguments(command, arguments);
	ft_lstclear(&arguments, NULL);
}

t_command	*parse_command(t_string_index *command_line, char **env)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (cmd);
	cmd->env = env;
	parse_command_data(command_line, cmd);
	if (cmd->arguments == NULL || cmd->arguments[0] == NULL)
	{
		free(cmd);
		cmd = NULL;
	}
	return (cmd);
}
