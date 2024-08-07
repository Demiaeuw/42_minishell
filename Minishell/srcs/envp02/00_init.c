/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:37:43 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/07 18:23:15 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    free_node2(t_envfinal *node)
{
	if (node)
	{
		free(node->type);
		free(node->content);
		free(node);
	}
}

// Fonction pour créer un nouveau nœud
t_envfinal	*create_env_node2(const char *type, const char *content)
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
void	add_env_node2(t_envfinal **env_list, t_envfinal *new_node)
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
void	init_env_list2(t_envfinal **env_list, char **envp)
{
	int			i;
	char		*key;
	char		*value;
	char		*sep;
	t_envfinal	*new_node;

	i = 0;
	while (envp[i])
	{
		sep = strchr(envp[i], '=');
		if (sep)
		{
			*sep = '\0';
			key = envp[i];
			value = sep + 1;
			new_node = create_env_node2(key, value);
			if (!new_node)
			{
				perror("Failed to create env node");
				break;
			}
			add_env_node2(env_list, new_node);
			*sep = '=';
		}
		i++;
	}
}

// Fonction pour afficher la liste chaînée des variables d'environnement
void	print_env_list2(t_envfinal *env_list)
{
	while (env_list)
	{
		printf("%s %s\n", env_list->type, env_list->content);
		env_list = env_list->next;
	}
}

// Fonction pour libérer la mémoire de la liste chaînée des variables d'environnement
void	free_env_list2(t_envfinal *env_list)
{
	t_envfinal *current;
	t_envfinal *next;

	current = env_list;
	while (current)
	{
		next = current->next;
		free_node2(current);
		current = next;
	}
}