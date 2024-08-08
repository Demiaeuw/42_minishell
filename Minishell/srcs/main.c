/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:39:22 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/08 18:46:35 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_token			*token_list;
	char 			*input;
	t_envfinal		*env_list = NULL;

	if (ac != 1)
		exit(EXIT_FAILURE);
	(void)av;

//test --------------------------------------------------------------------------------------------------------//
//fin de test -------------------------------------------------------------------------------------------------//
	main_env(&env_list, env);
	while (1)
	{
		display_prompt();
		input = read_input();
		token_list = main_parse(input);
		free(input);

		// // 4 - Exécution de la commande saisie par l'utilisateur
		// // selection builtin ou non
		main_builtin(token_list, env_list);
		// // si oui :
		// //		go la fonction qui gere les builtin
		// //				selection du builtin
		// // si non :
		// //		go EXECV


// test --------------------------------------------------------------------------------------------------------//
// fin test ----------------------------------------------------------------------------------------------------//

		free_token_list(&token_list, free_token_value);

	}
	free_env_list(env_list);
	return (0);
}
