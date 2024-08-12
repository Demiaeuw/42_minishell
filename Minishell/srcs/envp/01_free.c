/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:47:02 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/12 14:26:14 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	free_node(t_envfinal *node)
// {
// 	if (node)
// 	{
// 		free(node->type);
// 		free(node->content);
// 		free(node);
// 	}
// }

// /**
//  * Fonction pour libérer la mémoire de la liste chaînée
//  * des variables d'environnement
//  */
// void	free_env_list(t_envfinal *env_list)
// {
// 	t_envfinal	*current;
// 	t_envfinal	*next;

// 	current = env_list;
// 	while (current)
// 	{
// 		next = current->next;
// 		free_node(current);
// 		current = next;
// 	}
// }
