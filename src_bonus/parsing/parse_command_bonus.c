/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:36:03 by psalame           #+#    #+#             */
/*   Updated: 2024/02/28 19:37:39 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_Int_bonus.h"
#include "minishell_bonus.h"

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

static bool	is_command_empty(t_command *cmd)
{
	if (cmd->arguments != NULL && cmd->arguments[0] != NULL)
		return (false);
	if (cmd->argument_variables)
		return (false);
	if (cmd->infiles || cmd->outfiles)
		return (false);
	return (true);
}

t_command	*parse_command(t_string_index *command_line, char ***env)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (cmd);
	cmd->env = env;
	parse_command_data(command_line, cmd);
	if (is_command_empty(cmd))
	{
		free(cmd);
		cmd = NULL;
	}
	return (cmd);
}
