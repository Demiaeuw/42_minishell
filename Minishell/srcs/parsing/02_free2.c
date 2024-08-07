/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_free2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:11:20 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/07 16:38:30 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Libère la mémoire allouée pour une variable d'environnement (t_envp).
 */
void	free_envp_node(t_envp *envp)
{
	if (envp)
	{
		free(envp->key);
		free(envp->value);
		free(envp);
	}
}

/**
 * Libère la mémoire allouée pour la liste chaînée des variables d'environnement.
 */
void	free_env_list(t_env *envp_list)
{
	t_node *current;
	t_node *next;

	if (!envp_list || !envp_list->head)
		return;

	current = envp_list->head;
	while (current)
	{
		next = current->next;
		free_envp_node((t_envp *)current->content);
		free(current);
		current = next;
	}

	envp_list->head = NULL;
	envp_list->tail = NULL;
	envp_list->size = 0;
}

