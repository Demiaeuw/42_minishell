/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:55:16 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/10 19:18:06 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_history	*init_history(void)
{
	t_history	*history;

	history = (t_history *)malloc(sizeof(t_history));
	if (!history)
		return (NULL);
	history->cmd = NULL;
	history->next = NULL;
	history->prev = NULL;
	return (history);
}

void	save_history(t_history **history, char *cmd)
{
	t_history	*new_node;
	t_history	*current;

	new_node = (t_history *)malloc(sizeof(t_history));
	if (!new_node)
		return ;
	new_node->cmd = ft_strdup(cmd); // Remplace `ft_strdup` par une fonction d'allocation mémoire et de copie
	new_node->next = NULL;

	if (*history == NULL || (*history)->cmd == NULL)
	{
		free(*history);
		*history = new_node;
		new_node->prev = NULL;
	}
	else
	{
		current = *history;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
		new_node->prev = current;
	}
}

void	select_history(t_history *history)
{
	(void)history;
	// t_history	*current;
	printf("tet");
}

void	free_history(t_history *history)
{
	t_history	*current;
	t_history	*next;

	current = history;
	while (current)
	{
		next = current->next;
		free(current->cmd);  // Libère la mémoire pour la commande
		free(current);       // Libère le nœud de l'historique
		current = next;
	}
}

