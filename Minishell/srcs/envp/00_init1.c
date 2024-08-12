/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_init1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:24:44 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/12 14:34:50 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**env_dup(char **env)
{
	int		var_env;
	char	**dup_env;
	int		i;

	var_env = 0;
	i = 0;

	while(env(var_env) != NULL)
		var_env++;
	dup_env = malloc((var_env + 1) * sizeof(char *));
	while (i < var_env)
	{
		dup_env[i] = ft_strdup(env[i]);
		i++;
	}
	dup_env[var_env] = NULL;
	return(dup_env);
}
// void	main_env(t_envfinal **env, char **envp)
// {
// 	init_env_list(env, envp);
// 	increment_shlvl(*env);
// }

// /**
//  *  Fonction pour créer un nouveau nœud
//  */
// t_envfinal	*create_env_node(const char *type, const char *content)
// {
// 	t_envfinal	*node;

// 	node = (t_envfinal *)malloc(sizeof(t_envfinal));
// 	if (!node)
// 		return (NULL);
// 	node->type = strdup(type);
// 	if (!node->type)
// 	{
// 		free(node);
// 		return (NULL);
// 	}
// 	node->content = strdup(content);
// 	if (!node->content)
// 	{
// 		free(node->type);
// 		free(node);
// 		return (NULL);
// 	}
// 	node->next = NULL;
// 	return (node);
// }

// /**
//  *  Fonction pour ajouter un nœud à la liste chaînée
//  */
// void	add_env_node(t_envfinal **env_list, t_envfinal *new_node)
// {
// 	t_envfinal	*current;

// 	if (!*env_list)
// 	{
// 		*env_list = new_node;
// 		return ;
// 	}
// 	current = *env_list;
// 	while (current->next)
// 		current = current->next;
// 	current->next = new_node;
// }

// /**
//  *  Fonction pour initialiser la liste chaînée des variables d'environnement
//  */
// void	init_env_list(t_envfinal **env_list, char **envp)
// {
// 	int			i;
// 	char		*key;
// 	char		*value;
// 	char		*sep;
// 	t_envfinal	*new_node;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		sep = ft_strchr(envp[i], '=');
// 		if (sep)
// 		{
// 			*sep = '\0';
// 			key = envp[i];
// 			value = sep + 1;
// 			new_node = create_env_node(key, value);
// 			add_env_node(env_list, new_node);
// 			*sep = '=';
// 		}
// 		i++;
// 	}
// }
