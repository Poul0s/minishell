/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cache.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:55:52 by psalame           #+#    #+#             */
/*   Updated: 2024/01/23 13:55:52 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool is_in_cache(t_list *cache, void *data)
{
    bool    res;

    res = false;
    while (cache && !res)
    {
        if (cache->content == data)
            res = true;
        else
            cache = cache->next;
    }
    return (res);
}

bool    insert_exec_cache(t_command *command, void *data)
{
    t_list  *node;

    if (is_in_cache(command->execution_cache, data))
        return (true);
    node = ft_lstnew(data);
    if (!node)
        return (false);
    ft_lstadd_back(&(command->execution_cache), node);
    return (true);
}

void    delete_exec_cache(t_command *command)
{
    ft_lstclear(&(command->execution_cache), &free);
}
