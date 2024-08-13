/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:39:22 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/13 22:24:40 by acabarba         ###   ########.fr       */
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
	t_envp	envp;
	char	*input;

	signal(SIGINT, handle_sigint);
	if (ac != 1)
		exit(EXIT_FAILURE);
	(void)av;

	envp.env = env_dup(env);
	init_terminal(envp.env);

	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
			break ;
		if (*input)
			add_history(input);
		token_list = main_parsing(input);
		free(input);
		main_exec(token_list, &envp);
		free_token_list(token_list);
	}
	clear_history();
	return (0);
}