/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:03:47 by psalame           #+#    #+#             */
/*   Updated: 2024/02/16 14:10:30 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "command_Int.h"
#include "../variable_arguments_Int.h"

static char	*get_wildcard_part(ssize_t wildcard_pos, char *argument, size_t i)
{
	char	*res;

	if (wildcard_pos == -1)
		res = ft_substr(argument, i, ft_strlen(argument) - i);
	else
		res = ft_substr(argument, i, wildcard_pos - i);
	return (res);
}

static t_list	*convert_wildcard_arg(t_list *var_args, char *argument)
{
	t_list	*match_reg;
	t_list	*node;
	char	*part;
	ssize_t	next_wildcard;
	size_t	i;

	match_reg = NULL;
	i = 0;
	while (1)
	{
		next_wildcard = get_next_wildcard(&var_args);
		part = get_wildcard_part(next_wildcard, argument, i);
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
	}
	return (match_reg);
}

static int	is_file_corresponding(struct dirent *file, t_list *match_reg)
{
	char	*str;
	bool	folder;
	size_t	len;

	len = ft_strlen(match_reg->content);
	str = ft_strnstr(file->d_name, match_reg->content, len);
	if (!str)
		return (false);
	str += len;
	match_reg = match_reg->next;
	while (match_reg && match_reg->next != NULL)
	{
		len = ft_strlen(match_reg->content);
		str = ft_strnstr(file->d_name, match_reg->content, len);
		if (!str)
			return (false);
		str += len;
		match_reg = match_reg->next;
	}
	len = ft_strlen(match_reg->content);
	folder = (((char *) match_reg->content)[len - 1] == '/');
	if (ft_strlen(str) < len - folder || (folder && file->d_type != DT_DIR))
		return (false);
	str = str + ft_strlen(str) - len;
	return (!ft_strncmp(str, match_reg->content, ft_strlen(str) - folder));
}

void	restore_wildargument(t_list *var_args, t_command *command)
{
	t_variable_argument	*var_arg_data;
	char				*new_arg;
	ssize_t				next_wildcard;

	var_arg_data = var_args->content;
	next_wildcard = get_next_wildcard(&var_args);
	while (next_wildcard != -1)
	{
		new_arg = ft_str_insert(command->arguments[var_arg_data->arg_nb],
				"*",
				next_wildcard);
		if (new_arg)
		{
			free(command->arguments[var_arg_data->arg_nb]);
			command->arguments[var_arg_data->arg_nb] = new_arg;
		}
		next_wildcard = get_next_wildcard(&var_args);
	}
}

void	manage_wildcard(t_list *var_args, t_command *command)
{
	t_list				*files;
	DIR					*dir;
	t_list				*match_reg;
	char				*argument;
	t_variable_argument	*var_arg_data;

	var_arg_data = var_args->content;
	argument = command->arguments[var_arg_data->arg_nb];
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
