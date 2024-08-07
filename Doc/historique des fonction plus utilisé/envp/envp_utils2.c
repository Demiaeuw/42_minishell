/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:40:21 by gaesteve          #+#    #+#             */
/*   Updated: 2024/08/07 17:57:04 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * recup le premier noeud de la liste chainee et return un pointeur vers lui.
 */
t_node	*list_peek_first_node(t_env *list)
{
	return (list->head->next);
}

/**
 * insere un nouveau noeud a la fin de la liste (list).*
 */
void	list_append(t_env *list, t_node *new_node)
{
	t_node	*last_node;

	last_node = list->tail->prev;
	list->tail->prev = new_node;
	new_node->next = list->tail;
	new_node->prev = last_node;
	last_node->next = new_node;
	(list->size)++;
}

/**
 * pour creer une nouvelle liste vide.
 */
void	list_init(t_env *list)
{
	list->head = (t_node *)ft_calloc(1, sizeof(t_node));
	list->tail = (t_node *)ft_calloc(1, sizeof(t_node));
	list->head->next = list->tail;
	list->tail->prev = list->head;
	list->size = 0;
}

t_node	*new_node(void *content)
{
	t_node *new_node;

	new_node = (t_node*)ft_calloc(1, sizeof(t_node));
	new_node->content = content;
	return(new_node);
}

int	list_size(t_env *list)
{
	return(list->size);
}