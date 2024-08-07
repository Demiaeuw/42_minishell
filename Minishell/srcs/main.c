/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:39:22 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/07 19:51:10 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int	main(int ac, char **av, char **env)
// {
// 	t_env			envp_list;
// 	t_token			*token_list;
// 	// char **mini_env;
// 	char 			*input;

// 	// env_clone = env;

// 	if (ac != 1)
// 		exit(EXIT_FAILURE);
// 	(void)av;
// 	main_init_envp(&envp_list, env);// c est cense remplir les conditions 1 et 2

// 		// // 1 - Création de l'environnement.
// 			// main_init(mini_env, )

// 		// // 2 - Initialisation de l'environnement
// 	// signature(); //




// 		// // 3 - Interface créé avec les données de L'environement / While en boucle en attente de commande
// 		// // 3 - Parsing de la commande saisie par l'utilisateur (av de l'env)
// 			// while (1)
// 			// {
// 					display_prompt();
//         			input = read_input();
// 					token_list = main_parse(input);


// 					//token_list = main_parse(input); // potientiellement changer ac, av





// 		// // 4 - Exécution de la commande saisie par l'utilisateur
// 			// // selection builtin ou non
// 			// // si oui :
// 			// //		go la fonction qui gere les builtin
// 			// //				selection du builtin
// 			// // si non :
// 			// //		go EXECV

// 		// free token list
// 				// free_token_list(&token_list, free_token_value);


// 		// // 5 - Rendre la main à l'utilisateur pour prochaine commande
// 		// }


// 	// test --------------------------------------------------------------------------------------------------------//
// 	printf("\n\n%s\n\n", input);
// 	print_tokens(token_list);
// 	//printf("\n\nSHLVL=%d\n", shlvl->level);
// 	free_token_list(&token_list, free_token_value);
// 	// fin test ----------------------------------------------------------------------------------------------------//

// 	return (0);
// }



int	main(int ac, char **av, char **env)
{
	// t_env			envp_list;
	t_token			*token_list;
	char 			*input;
	t_envfinal *env_list = NULL;

	if (ac != 1)
		exit(EXIT_FAILURE);
	(void)av;

	int i = 0;

	// Initialisation des variables d'environnement
	// printf("0\n");//------------
	// main_init_envp(&envp_list, env);
	// printf("1\n");//------------



	
	//test
	init_env_list(&env_list, env);
	// print_env_list2(env_list);
	// fin de test 





	// // 1 - Création de l'environnement.
	// // 2 - Initialisation de l'environnement
	// signature(); //

	// Afficher la liste des variables d'environnement
	// print_env_list(&envp_list);
	// printf("2\n");
	// // 3 - Interface créé avec les données de L'environement / While en boucle en attente de commande
	// // 3 - Parsing de la commande saisie par l'utilisateur (av de l'env)
	 while (i < 2)
	 {
		display_prompt();
		input = read_input();
		token_list = main_parse(input);
		main_builtin(token_list, env_list);

		// // 4 - Exécution de la commande saisie par l'utilisateur
		// // selection builtin ou non
		// // si oui :
		// //		go la fonction qui gere les builtin
		// //				selection du builtin
		// // si non :
		// //		go EXECV

		// test --------------------------------------------------------------------------------------------------------//
		// printf("\n\n%s\n\n", input);
		// print_tokens(token_list);
		//printf("\n\nSHLVL=%d\n", shlvl->level);
		
		free_token_list(&token_list, free_token_value);
		free(input);
		i++;
		// fin test ----------------------------------------------------------------------------------------------------//
	 }
	free_env_list(env_list);

	return (0);
}