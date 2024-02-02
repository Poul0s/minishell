/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 21:03:09 by psalame           #+#    #+#             */
/*   Updated: 2024/02/02 16:27:52 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export_Int.h"

int	is_key_good_format(char *str)
{
	while (*str)
	{
		if (*str != '_' && !ft_isalnum(*str))
			return (false);
		str++;
	}
	return (true);
}

void	print_invalid_identifier(char *id, char *program_name)
{
	ft_dprintf(2, "%s: export: `%s': not a valid identifier\n",
				program_name, id);
}

static int	insert_single_env_var(char **arguments,
								char ***env,
								char *program_name)
{
	bool	good_format;
	int		i;

	good_format = true;
	i = 1;
	while (i <= 2)
	{
		if (!ft_isalpha(arguments[i][0]) && arguments[i][0] != '_')
		{
			good_format = false;
			print_invalid_identifier(arguments[i], program_name);
		}
		else if (!is_key_good_format(arguments[i]))
		{
			good_format = false;
			print_invalid_identifier(arguments[i], program_name);
		}
		i++;
	}
	if (good_format)
		*env = edit_env_var(*env, arguments[1], arguments[2]);
	return (!good_format);
}

static int	insert_multiple_env_var(char **arguments,
									char ***env,
									char *program_name)
{
	size_t	i;
	int		res;

	i = 0;
	res = 0;
	while (arguments[i])
	{
		res |= parse_env_var_data(arguments[i], env, program_name);
		i++;
	}
	return (res);
}

int	ft_export(char **arguments, char ***env, char *program_name)
{
	if (arguments[1] == NULL)
		return (print_env_sorted(*env, program_name));
	else
	{
		if (ft_strs_len(arguments) == 3
			&& ft_strchr(arguments[1], '=') == NULL
			&& ft_strchr(arguments[2], '=') == NULL)
			return (insert_single_env_var(arguments, env, program_name));
		else
			return (insert_multiple_env_var(arguments + 1, env, program_name));
	}
}
