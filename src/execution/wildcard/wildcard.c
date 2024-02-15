/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:03:47 by psalame           #+#    #+#             */
/*   Updated: 2024/02/15 16:33:29 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "command_Int.h"

static DIR	*open_current_dir(void)
{
	char	*cwd;
	DIR		*res;

	cwd = return_pwd();
	if (!cwd)
		return (NULL);
	res = opendir(cwd);
	free(cwd);
	return (res);
}

static t_list	*ls_dir(DIR **dir)
{
	t_list			*files;
	t_list			*node;
	struct dirent	*current_file;

	files = NULL;
	*dir = open_current_dir();
	if (!(*dir))
		return (NULL);
	current_file = readdir(*dir);
	while (current_file)
	{
		if (ft_strncmp(current_file->d_name, ".", 2) 
			&& ft_strncmp(current_file->d_name, "..", 3))
		{
			node = ft_lstnew(current_file);
			if (!node)
				ft_lstclear(&files, NULL);
			if (!node)
				break ;
			ft_lstadd_back(&files, node);
		}
		current_file = readdir(*dir);
	}
	return (files);
}

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
			else if (var_arg_data->argument_number != arg_number) // set var args to the next for keep arg number value
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
	if (folder)
		((char *)match_reg->content)[ft_strlen(match_reg->content) - 1] = 0;
	if (ft_strlen(filename) < ft_strlen(match_reg->content) || (folder && file->d_type != DT_DIR))
		return (false);
	filename = filename + ft_strlen(filename) - ft_strlen(match_reg->content);
	return (!ft_strncmp(filename, match_reg->content, ft_strlen(filename)));
}

char	*manage_wildcard(t_list *var_args, t_command *command)
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
		{
			// todo remake base argument with stars
		}
		else
		{
			sort_files(files);
			// todo separate into multiple arguments
			{
				while (files)
				{
					ft_printf("\'%s'\n", ((struct dirent *) files->content)->d_name);
					files = files->next;
				}
			}
		}
	}
	closedir(dir);
	return (NULL);
}
