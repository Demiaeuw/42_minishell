/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:39:22 by acabarba          #+#    #+#             */
/*   Updated: 2024/07/19 18:14:31 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av)
{ 
	char	*joined_args;

	// 1 - Création de l'environnement.
	// 2 - Initialisation de l'environnement
	// 3 - Environnement créé / While en boucle en attente de commande
	// 3 - Parsing de la commande saisie par l'utilisateur
	// 4 - Exécution de la commande saisie par l'utilisateur
	// 5 - Rendre la main à l'utilisateur pour prochaine commande
	
	// Appel de main_argument pour gérer les arguments
	joined_args = main_argument(ac, av);

	// Afficher la chaîne jointe créée dans step01
	if (joined_args)
		printf("Joined arguments: %s\n", joined_args);

	// Libérer la mémoire allouée pour joined_args
	free(joined_args);

	return (0);
}


