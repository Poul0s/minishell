/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_prompt_prefix.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:46:29 by psalame           #+#    #+#             */
/*   Updated: 2024/02/28 19:37:39 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	refresh_prompt(t_sh_data *shell_data)
{
	char	*username;
	char	*pwd;
	size_t	prompt_str_len;

	username = getenv("USER");
	pwd = get_path(shell_data->env);
	prompt_str_len = ft_strlen(username) + ft_strlen(shell_data->hostname)
		+ ft_strlen(pwd) + 5;
	if (shell_data->prompt)
		free(shell_data->prompt);
	shell_data->prompt = ft_calloc(prompt_str_len, sizeof(char));
	if (shell_data->prompt)
	{
		if (username)
			ft_strlcat(shell_data->prompt, username, prompt_str_len);
		ft_strlcat(shell_data->prompt, "@", prompt_str_len);
		if (shell_data->hostname)
			ft_strlcat(shell_data->prompt,
				shell_data->hostname, prompt_str_len);
		ft_strlcat(shell_data->prompt, ":", prompt_str_len);
		if (pwd)
			ft_strlcat(shell_data->prompt, pwd, prompt_str_len);
		ft_strlcat(shell_data->prompt, "$ ", prompt_str_len);
	}
	free(pwd);
}
