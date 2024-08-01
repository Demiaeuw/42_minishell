/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_mini_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:02:26 by gaesteve          #+#    #+#             */
/*   Updated: 2024/08/01 17:58:53 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//verifie d abord si le nombre d args est egal a 1, sinon ca genere une erreur
//ensuite on parcout la liste des variables de l environnement(envp_list)
//pour chaque variable, elle recupere la cle et la valeur.
//Si la valeur existe, affiche au format cle=valeur.
/*
	l utilisation : on l utilise pour afficher les variables de l env.
	exemple : si on veut connaitre le repertoire personnel de l utilisateur,
	on extrait la var HOME a partir de la liste de l env.

	Variables :
	cur_node : pointeur vers le noeud actuel dans la liste.
	key : la cle de la variable d environnement.
	value : la valeur associee a la cle.

	getenv reste une fonction plus simple pour recup une var specifique.

	cur_node est un pointeur sur le noeud actuel et nous permet de naviguer
	dans tous les noeuds de la liste.
*/
int	mini_env(char	**str, t_envlist *envp_list)
{
	t_node	*cur_node;
	char	*key;
	char	*value;

	if  (check_word_count(str) != 1)
	{
		gestion_erreur_bt("env", 0, MANY_ARG);
		return (EXIT_FAILURE);
	}
	cur_node = list_peek_first_node(envp_list);
	while (cur_node->next)
	{
		key = ((t_envp *)cur_node->content)->key;
		value = ((t_envp *)cur_node->content)->value;
		if (value)
			printf("%s=%s\n", key, value);
		cur_node = cur_node->next;
	}
	return(EXIT_SUCCESS);
}
