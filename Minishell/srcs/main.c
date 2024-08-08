/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:39:22 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/08 14:00:20 by acabarba         ###   ########.fr       */
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
	int i = 0;
//fin de test -------------------------------------------------------------------------------------------------//

	main_env(&env_list, env);
	while (i < 3)
	{
		display_prompt();
		input = read_input();
		token_list = main_parse(input);

		// // 4 - Exécution de la commande saisie par l'utilisateur
		// // selection builtin ou non
		main_builtin(token_list, env_list);
		// // si oui :
		// //		go la fonction qui gere les builtin
		// //				selection du builtin
		// // si non :
		// //		go EXECV


// test --------------------------------------------------------------------------------------------------------//
		i++;
// fin test ----------------------------------------------------------------------------------------------------//

		free_token_list(&token_list, free_token_value);
		free(input);

	}
	free_env_list(env_list);
	return (0);
}