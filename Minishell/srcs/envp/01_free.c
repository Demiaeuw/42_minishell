/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:47:02 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/07 19:51:50 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    free_node(t_envfinal *node)
{
	if (node)
	{
		free(node->type);
		free(node->content);
		free(node);
	}
}

// Fonction pour libérer la mémoire de la liste chaînée des variables d'environnement
void	free_env_list(t_envfinal *env_list)
{
	t_envfinal *current;
	t_envfinal *next;

	current = env_list;
	while (current)
	{
		next = current->next;
		free_node(current);
		current = next;
	}
}