/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:03:47 by psalame           #+#    #+#             */
/*   Updated: 2024/02/16 01:23:44 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "command_Int.h"

static ssize_t	get_next_wildcard(t_list **var_args, size_t index)
{
	t_variable_argument	*var_arg_data;
	size_t				arg_number;
	ssize_t				res;

	res = -1;
	if (var_args && *var_args)
	{
		arg_number = ((t_variable_argument *) (*var_args)->content)->argument_number;
		while (*var_args)
		{
			var_arg_data = (*var_args)->content;
			if (res == -1)
			{
				if (var_arg_data->argument_number == arg_number && var_arg_data->argument_index >= index)
					res = var_arg_data->argument_index;
				*var_args = (*var_args)->next;
			}
			else if (var_arg_data->argument_number != arg_number)
				*var_args = (*var_args)->next;
			else
				break ;
		}
	}
	return (res);
}

static t_list	*convert_wildcard_arg(t_list *var_args, char *argument) // todo function a tester un max
{
	t_list	*match_reg;
	t_list	*node;
	char	*part;
	ssize_t	next_wildcard;
	size_t	i;

	match_reg = NULL;
	i = 0;
	next_wildcard = get_next_wildcard(&var_args, i);
	while (1)
	{
		if (next_wildcard == -1)
			part = ft_substr(argument, i, ft_strlen(argument) - i);
		else
			part = ft_substr(argument, i, next_wildcard - i);
		node = ft_lstadd_back(&match_reg, ft_lstnew(part));
		if (!part || !node)
		{
			ft_lstclear(&match_reg, &free);
			free(part);
			return (NULL);
		}
		if (next_wildcard == -1)
			break ;
		i = next_wildcard;
		next_wildcard = get_next_wildcard(&var_args, i);
	}
	return (match_reg);
}

static int	is_file_corresponding(struct dirent *file, t_list *match_reg)
{
	char	*filename;
	bool	folder;

	filename = ft_strnstr(file->d_name, match_reg->content, ft_strlen(match_reg->content));
	if (!filename)
		return (false);
	filename += ft_strlen(match_reg->content);
	match_reg = match_reg->next;
	while (match_reg && match_reg->next != NULL)
	{
		filename = ft_strnstr(file->d_name, match_reg->content, ft_strlen(match_reg->content));
		if (!filename)
			return (false);
		filename += ft_strlen(match_reg->content);
		match_reg = match_reg->next;
	}
	folder = (((char *) match_reg->content)[ft_strlen(match_reg->content) - 1] == '/');
	if (ft_strlen(filename) < ft_strlen(match_reg->content) - folder || (folder && file->d_type != DT_DIR))
		return (false);
	filename = filename + ft_strlen(filename) - ft_strlen(match_reg->content);
	return (!ft_strncmp(filename, match_reg->content, ft_strlen(filename) - folder));
}

void	restore_wildargument(t_list *var_args, t_command *command)
{
	t_variable_argument	*var_arg_data;
	char				*new_arg;
	ssize_t				next_wildcard;
	
	var_arg_data = var_args->content;
	next_wildcard = get_next_wildcard(&var_args, 0);
	while (next_wildcard != -1)
	{
		new_arg = ft_str_insert(command->arguments[var_arg_data->argument_number], "*", next_wildcard);
		if (new_arg)
		{
			free(command->arguments[var_arg_data->argument_number]);
			command->arguments[var_arg_data->argument_number] = new_arg;
		}
		next_wildcard = get_next_wildcard(&var_args, next_wildcard);
	}
}

static void	move_variable_arguments_number(t_list *var_args)
{
	size_t	min_index;
	t_variable_argument	*var_arg_data;

	var_arg_data = var_args->content;
	min_index = var_arg_data->argument_number;
	while (var_args)
	{
		var_arg_data = var_args->content;
		if (var_arg_data->argument_number > min_index)
			var_arg_data->argument_number++;
		var_args = var_args->next;
	}
}

void	insert_wildarguments(t_list *var_args, t_list *files, t_command *cmd)
{
	char				*new_insert_arg;
	char				*new_arg;
	struct dirent		*file;
	size_t				i;
	t_variable_argument	*var_arg_data;

	file = files->content;
	new_arg = ft_strdup(file->d_name);
	var_arg_data = var_args->content;
	i = var_arg_data->argument_number + 1;
	while (files->next)
	{
		file = files->next->content;
		new_insert_arg = ft_strdup(file->d_name);
		if (new_insert_arg)
		{
			cmd->arguments = ft_strs_insert_str(cmd->arguments, new_insert_arg, i++);
			move_variable_arguments_number(var_args);
		}
		files = files->next;
	}
	if (new_arg)
		free(cmd->arguments[var_arg_data->argument_number]);
	if (new_arg)
		cmd->arguments[var_arg_data->argument_number] = new_arg;
}

void	manage_wildcard(t_list *var_args, t_command *command)
{
	t_list	*files;
	DIR		*dir;
	t_list	*match_reg;
	char	*argument;

	argument = command->arguments[((t_variable_argument *) var_args->content)->argument_number];
	files = ls_dir(&dir);
	if (files)
	{
		match_reg = convert_wildcard_arg(var_args, argument);
		ft_lstremoveif(&files, match_reg, NULL, &is_file_corresponding);
		ft_lstclear(&match_reg, free);
		if (files == NULL)
			restore_wildargument(var_args, command);
		else
		{
			sort_files(files);
			insert_wildarguments(var_args, files, command);
		}
	}
	closedir(dir);
}
