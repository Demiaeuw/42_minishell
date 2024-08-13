/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:39:22 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/13 23:23:34 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//debut de test
// static void	display_prompt(void)
// {
// 	write(STDOUT_FILENO, "minishell> ", 12);
// }

// static char	*read_input(void)
// {
// 	char *buffer = (char*)malloc(sizeof(char) * BUFFER_SIZE);
// 	ssize_t bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
// 	if (bytes_read < 0)
// 	{
// 		free(buffer);
// 		return NULL;
// 	}
// 	buffer[bytes_read] = '\0';
// 	return (buffer);
// }
//fin de test

int	main(int ac, char **av, char **env)
{
	t_token	*token_list;
	t_envp	*envp;  // Déclare envp comme un pointeur vers t_envp
	char	*input;

	signal(SIGINT, handle_sigint);
	if (ac != 1)
		exit(EXIT_FAILURE);
	(void)av;

	envp = (t_envp *)malloc(sizeof(t_envp));  // Allocation dynamique de t_envp
	if (envp == NULL)  // Vérifie si l'allocation a échoué
		exit(EXIT_FAILURE);
	envp->env = env_dup(env).env;  // Initialisation de env dans envp
	init_terminal(envp);  // Initialiser le terminal

	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
			break ;
		if (*input)
			add_history(input);
		token_list = main_parsing(input);
		free(input);
		main_exec(token_list, envp);  // Passe le pointeur envp
		free_token_list(token_list);
	}
	clear_history();
	// free_t_envp(envp);
	return (0);
}