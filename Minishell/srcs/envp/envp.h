/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:40:48 by gaesteve          #+#    #+#             */
/*   Updated: 2024/07/24 15:42:27 by gaesteve         ###   ########.fr       */
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

typedef struct s_list
{
	int			size;
	t_node *head;
	t_node	*tail;
}	t_list;

/*			MAIN FUNCTIONS			*/
void	envp_init(t_list *envp_list, char **envp);
void	envp_add(t_list *envp_list, char *key, char *value);
int		envp_exist(t_list *envp_list, char *key);
char	*envp_find(t_list *envp_list, char *key);
void	envp_edit(t_list *envp_list, char *key, char *value);

/*			UTILS FUNCTIONS			*/
void	envp_delete(t_list *envp_list, char *key);
char	**envp_convert(t_list *envp_list);
char	*str3join(char *str1, char *str2, char *str3);
char	*ft_strcat(char *dest, char *src);
void	list_init(t_list *list);
int		list_size(t_list *list);
void	list_append(t_list *list, t_node *new_node);
t_node	*list_peek_first_node(t_list *list);

#endif
