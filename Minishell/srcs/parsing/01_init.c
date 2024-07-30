/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 19:23:03 by acabarba          #+#    #+#             */
/*   Updated: 2024/07/30 11:22:21 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Fonction de création de Noeud pour la liste TOKEN :
 * Necessite :
 * Le type de TOKEN
 * ce qu'il contient (la value correspond au contenue du TOKEN)
 */
t_token	*create_token(token_type type, char *value)
{
	t_token	*token;

	token = safe_malloc(sizeof(t_token));
	token->type = type;
	token->value = ft_strdup(value);
	token->is_builtin = false;
	token->is_last_command = false;
	token->next = NULL;
	return (token);
}

/**
 * Fonction pour ajouter un token a la liste chainé
 * Créer un nouveau si la liste est vide
 */
void	add_token(t_token **token_list, t_token *new_token)
{
	t_token	*current;

	if (*token_list == NULL)
	{
		*token_list = new_token;
	}
	else
	{
		current = *token_list;
		while (current->next != NULL)
			current = current->next;
		current->next = new_token;
	}
}

/**
 * Fonction de création de Malloc avec la vérification 
 */
void	*safe_malloc(size_t bytes)
{
	void	*ptr;

	ptr = malloc(bytes);
	if (ptr == NULL)
		main_error(ft_error, 3);
	return (ptr);
}
