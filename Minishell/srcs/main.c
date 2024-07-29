/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:39:22 by acabarba          #+#    #+#             */
/*   Updated: 2024/07/29 12:40:49 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **env)
{ 
	t_token	*token_list;

	// // 1 - Création de l'environnement.
	// // 2 - Initialisation de l'environnement
	// // 3 - Environnement créé / While en boucle en attente de commande
	// // 3 - Parsing de la commande saisie par l'utilisateur
	
	// 	// Appel de main_argument pour gérer les arguments
	// args = main_argument(ac, av); 

	// // 4 - Exécution de la commande saisie par l'utilisateur
	// // 5 - Rendre la main à l'utilisateur pour prochaine commande
	

	// test 

	// Appel de main_argument pour gérer les arguments
	token_list = main_argument(ac, av);

	// Afficher les tokens
	print_tokens(token_list);

	// Libérer la mémoire allouée pour la liste de tokens
	free_token_list(&token_list, free_token_value);
	// fin test
	return (0);
}
