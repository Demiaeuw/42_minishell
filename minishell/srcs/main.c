/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpourcel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:39:22 by acabarba          #+#    #+#             */
/*   Updated: 2024/09/26 12:33:40 by kpourcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_status_cmd;
/*
int	main(int ac, char **av, char **env)
{
	t_signal			handler;
	t_envp				*envp;

	if (ac != 1)
		exit(EXIT_FAILURE);
	(void)av;
	init_signal();
	envp = (t_envp *)malloc(sizeof(t_envp));
	if (envp == NULL)
		exit(EXIT_FAILURE);
	envp->env = env_dup(env).env;
	init_terminal(envp);
	g_status_cmd = 0;
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
*/

int	main(int ac, char **av, char **env)
{
	t_signal	handler;
	t_envp		*envp;

	if (ac != 1)
		exit(EXIT_FAILURE);
	(void)av;
	init_signal();
	envp = NULL;
	init_minishell(&envp, env);
	g_status_cmd = 0;
	main_loop(envp, &handler);
	cleanup_and_exit(envp);
	return (0);
}

void	init_minishell(t_envp **envp, char **env)
{
	*envp = (t_envp *)malloc(sizeof(t_envp));
	if (*envp == NULL)
		exit(EXIT_FAILURE);
	(*envp)->env = env_dup(env).env;
	init_terminal(*envp);
}

void	main_loop(t_envp *envp, t_signal *handler)
{
	char		*input;
	t_token		*token_list;

	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
		{
			write(1, "exit\n", 5);
			cleanup_and_exit(envp);
		}
		if (*input && !check_onlyspace(input))
		{
			add_history(input);
			token_list = main_parsing(input, envp);
			free(input);
			main_exec(token_list, envp, handler);
			free_token_list(token_list);
		}
		else
			free(input);
	}
}

void	cleanup_and_exit(t_envp *envp)
{
	clear_history();
	free_t_envp(envp);
	exit(0);
}
