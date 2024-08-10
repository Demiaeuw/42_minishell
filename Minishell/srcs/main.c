/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:39:22 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/10 22:30:45 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_token			*token_list;
	t_envfinal		*env_list = NULL;
	char 			*input;

	signal(SIGINT, handle_sigint);
	if (ac != 1)
		exit(EXIT_FAILURE);
	(void)av;

	main_env(&env_list, env);

	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
			break ;
		if (*input)
			add_history(input);
		token_list = main_parse(input);
		free(input);
		main_exec(token_list, env_list);
		free_token_list(&token_list, free_token_value);
	}
	free_env_list(env_list);
	clear_history();
	return (0);
}
