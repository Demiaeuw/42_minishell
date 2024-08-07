/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:40:48 by gaesteve          #+#    #+#             */
/*   Updated: 2024/08/07 16:50:29 by acabarba         ###   ########.fr       */
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

//head and tail = dummy nodes(noeuds qui contient rien, juste une facon
//pratique pour la gestion de la liste).
typedef struct s_env
{
	int				size;
	// char			*categorie;
	// char			*value;
	t_node			*head;
	t_node			*tail;
	// struct s_env	*next;
}	t_env;

/*			MAIN FUNCTIONS			*/
void	envp_init(t_env *envp_list, char **envp);
void	envp_add(t_env *envp_list, char *key, char *value);
int		envp_exist(t_env *envp_list, char *key);
char	*envp_find(t_env *envp_list, char *key);
void	envp_edit(t_env *envp_list, char *key, char *value);

/*			UTILS FUNCTIONS			*/
void	envp_delete(t_env *envp_list, char *key);
char	**envp_convert(t_env *envp_list);
char	*str3join(char *str1, char *str2, char *str3);
void	list_init(t_env *list);
int		list_size(t_env *list);
void	list_append(t_env *list, t_node *new_node);
t_node	*list_peek_first_node(t_env *list);
/*			Printenv				*/
void	print_env_list(t_env *env);


#endif
