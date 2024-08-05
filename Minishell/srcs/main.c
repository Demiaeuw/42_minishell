/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:39:22 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/05 14:54:12 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av)
{ 
	t_token	*token_list;
	t_shell_level *shlvl;
	
		// // 1 - Création de l'environnement.
		// envp_init()
		// // 2 - Initialisation de l'environnement
		// shlvl = init_shlvl();
		// while (1)
		// {
		// // 3 - Environnement créé / While en boucle en attente de commande
		// signature();
		// // 3 - Parsing de la commande saisie par l'utilisateur (av de l'env)
		token_list = main_parse(ac, av);
		// getchar();

		// // 4 - Exécution de la commande saisie par l'utilisateur
			// // selection builtin ou non 
			// // si oui :
			// //		go la fonction qui gere les builtin
			// //				selection du builtin
			// // si non :
			// //		go EXECV
		// free token list
		// // 5 - Rendre la main à l'utilisateur pour prochaine commande
		}
	

	// test 
	print_tokens(token_list);
	printf("\n\nSHLVL=%d\n", shlvl->level);
	free_token_list(&token_list, free_token_value);
	free_shlvl(shlvl);
	// fin test
	
	return (0);
}
