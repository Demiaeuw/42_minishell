/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:39:22 by acabarba          #+#    #+#             */
/*   Updated: 2024/09/23 16:56:56 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

pid_t	g_status_cmd;

int	main(int ac, char **av, char **env)
{
	t_signal			handler;
	t_envp				*envp;

	if (ac != 1)
		exit(EXIT_FAILURE);
	(void)av;
	init_signal_handlers(&handler);
	envp = (t_envp *)malloc(sizeof(t_envp));
	if (envp == NULL)
		exit(EXIT_FAILURE);
	g_status_cmd = 0;
	envp->env = env_dup(env).env;
	init_terminal(envp);
	while (1)
	{
		char *input = readline("minishell> ");
		if (input == NULL)
		{
			write(1, "exit\n", 5);
			free_t_envp(envp);
			clear_history();
			exit(0);
		}
		if (*input && !check_onlyspace(input))
		{
			add_history(input);
			t_token *token_list = main_parsing(input, envp);
			free(input);
			//print_token_list(token_list); // test parsing
			main_exec(token_list, envp, &handler);
			free_token_list(token_list);
		}
		else
			free(input);
	}
	clear_history();
	free_t_envp(envp);
	return (0);
}
