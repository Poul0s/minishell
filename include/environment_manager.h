/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_manager.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:10:11 by psalame           #+#    #+#             */
/*   Updated: 2024/01/17 17:25:51 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_MANAGER_H
# define ENVIRONMENT_MANAGER_H

# include "libft.h"

typedef struct s_env_data
{
	char				*key;
	char				*value;
	struct s_env_data	*next;
}	t_env_data;

t_env_data	*convert_strs_to_env_data(char **env);
char		**convert_env_data_to_strs(t_env_data *env_data);
t_env_data	*get_env_data(t_env_data *env_data, char *key);
char		*get_env_value(t_env_data *env_data, char *key);

typedef struct s_env_tree
{
	t_env_data	*env;
	t_list		*childrens; // t_list of t_env_tree: each modification on env will modify on each childrens
}	t_env_tree;

t_env_tree	*create_env_tree(t_env_tree *parent, char **env); // todo remove parent bc forcement le parent le plus haut
t_env_tree	*create_env_tree_children(t_env_tree *parent);
void		add_env_tree_children(t_env_tree *parent, t_env_tree *children);
void		edit_env_var(t_env_tree *env_tree, char *key, char *data);
void		del_env_var(t_env_tree *env_tree, char *key);

#endif