/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 19:23:03 by acabarba          #+#    #+#             */
/*   Updated: 2024/07/17 15:34:35 by yonieva          ###   ########.fr       */
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
	t_token *token;

	token = safe_malloc(sizeof(t_token));
	token->type = type;
	token->value = ft_strdup(value);
	token->next = NULL;
	return (token);
}
