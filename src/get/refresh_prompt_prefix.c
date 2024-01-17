/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_prompt_prefix.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:46:29 by psalame           #+#    #+#             */
/*   Updated: 2024/01/15 15:41:11 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	refresh_prompt(t_sh_data *shell_data)
{
	char	*username;
	char	*pwd;
	size_t	prompt_str_len;

	username = getenv("USER");
	pwd = get_path();
	prompt_str_len = ft_strlen(username) +
				ft_strlen(shell_data->hostname) +
				ft_strlen(pwd) + 5;
	shell_data->prompt = malloc(prompt_str_len);
	if (shell_data->prompt)
	{
		shell_data->prompt[0] = 0;
		ft_strlcat(shell_data->prompt, username, prompt_str_len);
		ft_strlcat(shell_data->prompt, "@", prompt_str_len);
		ft_strlcat(shell_data->prompt, shell_data->hostname, prompt_str_len);
		ft_strlcat(shell_data->prompt, ":", prompt_str_len);
		ft_strlcat(shell_data->prompt, pwd, prompt_str_len);
		ft_strlcat(shell_data->prompt, "$ ", prompt_str_len);
	}
	// free(username);
	free(pwd);
}
