/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:02:49 by psalame           #+#    #+#             */
/*   Updated: 2024/01/19 16:09:06 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef EXECUTION_H
# define EXECUTION_H

# include <sys/types.h>
# include <sys/wait.h>

int		execute_command_line(t_command_group *command_line);
char	*find_cmd(char *cmd, char **path);

#endif