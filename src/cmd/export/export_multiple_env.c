/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_multiple_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:52:06 by psalame           #+#    #+#             */
/*   Updated: 2024/02/02 15:20:12 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export_Int.h"

static int	set_env_var_data(char *key, char *value, char ***env, bool append)
{
	char	*prev_env_var;

	if (append)
		prev_env_var = get_env_var(*env, key);
	if (append && prev_env_var)
	{
		value = ft_strjoin(prev_env_var, value);
		if (value)
		{
			*env = edit_env_var(*env, key, value);
			free(value);
		}
		else
			return (ENOMEM);
	}
	else
		*env = edit_env_var(*env, key, value);
	return (0);
}

static char	*detect_sep(char *argument, bool *append)
{
	char	*sep;

	*append = false;
	sep = ft_strchr(argument, '=');
	if (sep)
	{
		*sep = 0;
		if (*(sep - 1) == '+')
		{
			*append = true;
			*(sep - 1) = 0;
		}
	}
	return (sep);
}

int	parse_env_var_data(char *argument, char ***env, char *shell_name)
{
	char	*sep;
	bool	append;
	int		res;

	if (!ft_isalpha(argument[0]) && argument[0] != '_')
	{
		print_invalid_identifier(argument, shell_name);
		return (1);
	}
	sep = detect_sep(argument, &append);
	if (!is_key_good_format(argument))
	{
		if (sep)
			*sep = '=';
		if (sep && append)
			*(sep - 1) = '+';
		print_invalid_identifier(argument, shell_name);
		return (1);
	}
	if (!sep)
		return (0);
	res = set_env_var_data(argument, sep + 1, env, append);
	if (res)
		ft_dprintf(2, "%s: export: `%s': %s\n", shell_name, argument, strerror(res));
	return (res);
}
