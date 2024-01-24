/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:21:11 by psalame           #+#    #+#             */
/*   Updated: 2024/01/24 17:27:20 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_argument_variable(void *data)
{
	t_variable_argument	*variable_argument;

	variable_argument = data;
	if (variable_argument)
	{
		free(variable_argument->data);
		free(variable_argument);
	}
}

void	free_command(t_command *command)
{
	ft_free_strs(command->arguments);
	ft_lstclear(&(command->infiles), &free);
	ft_lstclear(&(command->outfiles), &free);
	ft_lstclear(&(command->argument_variables), &free_argument_variable);
	free(command);
}

void	free_command_line(t_command_group *command_line, bool reset)
{
	static t_list	*commands_grp_free = NULL;
	t_list			*current_command_grp_node;

	if (reset)
	{
		ft_lstclear(&commands_grp_free, NULL);
		return ;
	}
	if (!command_line)
		return ;
	current_command_grp_node = commands_grp_free;
	while (current_command_grp_node)
	{
		if (current_command_grp_node->content == command_line)
			return ;
		current_command_grp_node = current_command_grp_node->next;
	}
	while (current_command_grp_node == NULL)
		current_command_grp_node = ft_lstnew(command_line);
	ft_lstadd_back(&commands_grp_free, current_command_grp_node);
	free_command(command_line->command);
	free_command_line(command_line->on_error, false);
	free_command_line(command_line->on_success, false);
	free_command_line(command_line->pipe_next, false);
	free(command_line);
}
