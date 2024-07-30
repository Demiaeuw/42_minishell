/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_mini_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:14:09 by gaesteve          #+#    #+#             */
/*   Updated: 2024/07/30 17:20:02 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Utilisation : pour supprimer des variables d envrionnement d une liste.
 *
 * Exemple : si on fait unset VAR1, ca supprimera VAR1 de la liste des var
 * d environnement
 *
 * on utilise is proper env pour verifier que l arg actuel est un nom de var
 * d environnement valide.
 * si l arg n est pas valide on appelle notre gestion d erreur.
 *
 * si l arg est valide, on le stocke dans key.
 * et on apelle envp delete pour suppr la var d environnement qui correspond
 * de la liste envp_list
*/
int	mini_unset(char **cmd_vector, t_envlist *envp_list)
{
	int		error_flag;
	int		i;
	char	*key;

	error_flag = EXIT_SUCCESS;
	i = 1;
	while (cmd_vector[i])
	{
		if (!is_proper_env(cmd_vector[i]))
		{
			error_flag = EXIT_FAILURE;
			gestion_erreur_bt("unset", cmd_vector[i], INVALID_ARG);
			i++;
			continue ;
		}
		else
		{
			key = cmd_vector[i];
			envp_delete(envp_list, key);
			i++;
		}
		return (error_flag);
	}
}
