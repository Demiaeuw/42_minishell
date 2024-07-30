/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:39:22 by acabarba          #+#    #+#             */
/*   Updated: 2024/07/30 13:16:33 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av)
{ 
	t_token	*token_list;
	printf("Mini_Shell 42 [version 10.0.22631.3958]\n");
	printf("(c) Gardiens de Phare [GDP]. Tous droits réservés.\n\n\n");
	// // 1 - Création de l'environnement.
	// // 2 - Initialisation de l'environnement
	// // 3 - Environnement créé / While en boucle en attente de commande
	// // 3 - Parsing de la commande saisie par l'utilisateur
	
	// 	// Appel de main_argument pour gérer les arguments
	// args = main_argument(ac, av); 

	// // 4 - Exécution de la commande saisie par l'utilisateur
	// // 5 - Rendre la main à l'utilisateur pour prochaine commande
	

	// test 
	token_list = main_parse(ac, av);

	print_tokens(token_list);

	free_token_list(&token_list, free_token_value);
	// fin test
	return (0);
}
