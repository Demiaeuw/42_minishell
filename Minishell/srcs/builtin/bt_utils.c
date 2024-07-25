/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:42:03 by gaesteve          #+#    #+#             */
/*   Updated: 2024/07/25 16:12:49 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_word_count(char **cmd_vector)
{
	int	i;

	i = 0;
	while (cmd_vector[i])
		i++;
	return (i);
}

void	gestion_erreur_bt()
{

}
