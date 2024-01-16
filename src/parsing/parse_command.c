/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:36:03 by psalame           #+#    #+#             */
/*   Updated: 2024/01/16 01:06:53 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_Int.h"
#include "minishell.h"

void	parse_command(t_string_index *command_line, t_command *command)
{
	t_list	*arguments;
	char	*argument;
	size_t	i;

	while (command_line->str[command_line->i] == ' ')
		command_line->i++;
	arguments = NULL;
	argument = parse_argument(command_line, command);
	while (argument)
	{
		ft_lstadd_back(&arguments, ft_lstnew(argument)); // todo free argument if ft_lstnew fail
		argument = parse_argument(command_line, command);
	}
	if (ft_lstsize(arguments) == 0)
		return ;
	command->executable = arguments->content;
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

// todo parse infile outfile heredocuments
