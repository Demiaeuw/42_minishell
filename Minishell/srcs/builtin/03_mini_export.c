/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_mini_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:33:06 by gaesteve          #+#    #+#             */
/*   Updated: 2024/08/12 16:03:47 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * BUT DE LA FONCTION : avec cette commande on peut ajouter ou modifier des var
 * de l env dans la liste des var d env du shell.
 *
 * par exemple si on veut ajouter une nouvelle variable :
 * export PATH=/usr/local/bin
 * separe PATH et /usr/local/bin grace au =,
 * check si PATH est valide,
 * ajoute PATH a la liste de var d env avec la valeur /usr/local/bin.
 * si on fait ensuite PATH=/usr/bin ca va modifier sa valeur avec la nouvelle
 * qu on vient de lui donner.
 */
void	exe_export(t_token *token, char **env)
{
	int		i;
	
}
