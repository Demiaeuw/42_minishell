/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:49:03 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/14 20:55:10 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Gestion des redirections
 * 
 * Il faut init la struct t_chevron et la remplir avec des valeurs de bases.
 * Il faut attribué la pointeur vers cette nouvelle liste chainé t_chevron chaque noeud de t_token.
 * Parsing de token->value pour repéré les chevron et les attribué comme ils devraient avec l'enum
 * 
 */