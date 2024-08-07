/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:37:43 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/07 19:54:38 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Fonction pour créer un nouveau nœud
t_envfinal	*create_env_node(const char *type, const char *content)
{
	t_envfinal *node;

	node = (t_envfinal *)malloc(sizeof(t_envfinal));
	if (!node)
		return (NULL);
	node->type = strdup(type);
	if (!node->type)
	{
		free(node);
		return (NULL);
	}
	node->content = strdup(content);
	if (!node->content)
	{
		free(node->type);
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

// Fonction pour ajouter un nœud à la liste chaînée
void	add_env_node(t_envfinal **env_list, t_envfinal *new_node)
{
	t_envfinal *current;

	if (!*env_list)
	{
		*env_list = new_node;
		return;
	}
	current = *env_list;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

// Fonction pour initialiser la liste chaînée des variables d'environnement
void	init_env_list(t_envfinal **env_list, char **envp)
{
	int			i;
	char		*key;
	char		*value;
	char		*sep;
	t_envfinal	*new_node;

	i = 0;
	while (envp[i])
	{
		sep = ft_strchr(envp[i], '=');
		if (sep)
		{
			*sep = '\0';
			key = envp[i];
			value = sep + 1;
			new_node = create_env_node(key, value);
			if (!new_node)
			{
				perror("Failed to create env node");
				break;
			}
			add_env_node(env_list, new_node);
			*sep = '=';
		}
		i++;
	}
}

// Fonction pour afficher la liste chaînée des variables d'environnement
void	print_env_list(t_envfinal *env_list)
{
	while (env_list)
	{
		printf("%s %s\n", env_list->type, env_list->content);
		env_list = env_list->next;
	}
}

