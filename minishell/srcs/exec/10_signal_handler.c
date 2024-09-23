/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:57:36 by acabarba          #+#    #+#             */
/*   Updated: 2024/09/23 18:16:02 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//Traite et réinitialise les signaux dans le processus parent après
//l'exécution d'une commande.
void	handle_signals_in_parent(t_signal *handler)
{
	if (handler->sigint)
	{
		write(1, "\n", 1);
		handler->sigint = 0;
	}
	if (handler->sigquit)
		handler->sigquit = 0;
	if (handler->sigterm)
		handler->sigterm = 0;
}

//Intercepte immédiatement le signal lorsqu'il est reçu (comme CTRL+C, SIGTERM).
void	signal_handler(int sig, siginfo_t *info, void *context)
{
	t_signal	*handler;

	(void)info;
	handler = (t_signal *)context;
	if (sig == SIGINT)
	{
		handler->sigint = 1;
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGTERM)
	{
		handler->sigterm = 1;
		write(1, "Exit shell\n", 11);
		exit(0);
	}
}

//initialise des signaux qui enregistre les gestionnaires pour les signaux que
//tu veux capturer (comme SIGINT, SIGQUIT, SIGTERM).
void	init_signal_handlers(t_signal *handler)
{
	struct sigaction	sa;

	sa.sa_sigaction = signal_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, (void *)handler);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	sa.sa_sigaction = signal_handler;
	sigaction(SIGTERM, &sa, (void *)handler);
}

//lance un processus enfant avec fork() et redéfinit les signaux dans le
//processus enfant.
pid_t	fork_and_execute(char *cmd_path, char **split_args, t_envp *envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTERM, SIG_DFL);
		execute_child_process(cmd_path, split_args, envp);
	}
	return (pid);
}
