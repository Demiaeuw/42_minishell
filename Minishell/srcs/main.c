/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:39:22 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/26 20:27:21 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_signal			handler;
	t_envp				*envp;

	if (ac != 1)
		exit(EXIT_FAILURE);
	(void)av;

	// Initialisation des signaux
	init_signal_handlers(&handler);

	// Initialisation de l'environnement
	envp = (t_envp *)malloc(sizeof(t_envp));
	if (envp == NULL)
		exit(EXIT_FAILURE);
	envp->env = env_dup(env).env;
	init_terminal(envp);
	while (1)
	{
		// Lire et gérer l'entrée de l'utilisateur
		char *input = readline("minishell> ");
		if (input == NULL)
		{
			write(1, "exit\n", 5);
			break;
		}
		if (*input)
		{
			add_history(input);
			t_token *token_list = main_parsing(input, envp);
			free(input);
			//print_token_list(token_list); // test parsing
			main_exec(token_list, envp, &handler);  // Passe le handler ici
			free_token_list(token_list);
		}
		else
		{
			free(input);
		}
	}
	clear_history();
	free_t_envp(envp);
	return (0);
}
