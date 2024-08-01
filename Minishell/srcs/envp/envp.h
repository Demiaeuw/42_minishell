/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:40:48 by gaesteve          #+#    #+#             */
/*   Updated: 2024/08/01 17:00:02 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_H
# define ENVP_H

#include "../../include/utils/libft/libft.h"
#include "../../include/minishell.h"

typedef struct s_envp
{
	char	*key;
	char	*value;
}	t_envp;

typedef struct s_node
{
	void			*content;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

typedef struct s_envlist
{
	int			size;
	t_node		*head;
	t_node		*tail;
}	t_envlist;

/*			MAIN FUNCTIONS			*/
void	envp_init(t_envlist *envp_list, char **envp);
void	envp_add(t_envlist *envp_list, char *key, char *value);
int		envp_exist(t_envlist *envp_list, char *key);
char	*envp_find(t_envlist *envp_list, char *key);
void	envp_edit(t_envlist *envp_list, char *key, char *value);

/*			UTILS FUNCTIONS			*/
void	envp_delete(t_envlist *envp_list, char *key);
char	**envp_convert(t_envlist *envp_list);
char	*str3join(char *str1, char *str2, char *str3);
// char	*ft_strcat(char *dest, char *src);
void	list_init(t_envlist *list);
int		list_size(t_envlist *list);
void	list_append(t_envlist *list, t_node *new_node);
t_node	*list_peek_first_node(t_envlist *list);

#endif
