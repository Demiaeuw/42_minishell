/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:39:22 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/06 01:28:11 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **env)
{ 
	t_token	*token_list;
	// char **mini_env;
	char *input;

	// env_clone = env;
	
	if (ac != 1)
		exit(EXIT_FAILURE);
	(void)av;
	(void)env;

	
		// // 1 - Création de l'environnement.
			// main_init(mini_env, )


			
			
		// // 2 - Initialisation de l'environnement
	// signature(); //
	


	
		// // 3 - Interface créé avec les données de L'environement / While en boucle en attente de commande
		// // 3 - Parsing de la commande saisie par l'utilisateur (av de l'env)
			// while (1)
			// {
					display_prompt();
        			input = read_input();
					token_list = main_parse(input);

	
					//token_list = main_parse(input); // potientiellement changer ac, av





		// // 4 - Exécution de la commande saisie par l'utilisateur
			// // selection builtin ou non 
			// // si oui :
			// //		go la fonction qui gere les builtin
			// //				selection du builtin
			// // si non :
			// //		go EXECV
			
		// free token list
				// free_token_list(&token_list, free_token_value);

		
		// // 5 - Rendre la main à l'utilisateur pour prochaine commande
		// }
	

	// test --------------------------------------------------------------------------------------------------------//
	printf("\n\n%s\n\n", input);
	print_tokens(token_list);
	//printf("\n\nSHLVL=%d\n", shlvl->level);
	free_token_list(&token_list, free_token_value);
	// fin test ----------------------------------------------------------------------------------------------------//
	
	return (0);
}
