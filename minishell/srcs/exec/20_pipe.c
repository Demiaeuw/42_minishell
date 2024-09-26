/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 02:35:38 by acabarba          #+#    #+#             */
/*   Updated: 2024/09/26 19:12:41 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Fonction pour gérer la création et l'exécution des processus
void	handle_p(t_process_data *args, int *fd_in, int *pipefd, pid_t *last_pid)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		// Enfant : configuration des redirections
		if (args->in != STDIN_FILENO)
		{
			dup2(args->in, STDIN_FILENO);
			close(args->in);
		}
		if (args->out != STDOUT_FILENO)
		{
			dup2(args->out, STDOUT_FILENO);
			close(args->out);
		}
		// Fermer le pipe pour les processus intermédiaires
		if (args->token->next && args->token->next->type == TOKEN_PIPE)
		{
			close(pipefd[0]);
		}
		// Exécuter la commande ou le builtin
		if (builtin_check(args->token))
			builtin_selector(args->token, args->envp);
		else
			execute_execve(args->token, args->envp, args->handler);
		exit(EXIT_FAILURE);  // Assure que l'enfant termine bien
	}
	else
	{
		*last_pid = pid;  // Stocker le PID du dernier processus
		// Parent : fermeture des descripteurs inutilisés
		if (*fd_in != 0)
			close(*fd_in);
		if (pipefd[1] != -1)
			close(pipefd[1]);
		*fd_in = pipefd[0];  // Préparer l'entrée pour le prochain processus
	}
}

// Fonction principale de gestion des pipes
void execute_pipes(t_token *token, t_envp *envp, t_signal *handler)
{
	int pipefd[2];
	int fd_in = 0;  // Entrée initiale
	pid_t last_pid = 0;
	t_process_data args;

	args.envp = envp;
	args.handler = handler;

	// Création et gestion des processus
	while (token)
	{
		if (token->type == TOKEN_COMMAND)
		{
			args.token = token;
			create_pipe_if_needed(pipefd, token);
			setup_process_args(&args, fd_in, pipefd);
			handle_p(&args, &fd_in, pipefd, &last_pid);
		}
		token = token->next;
	}
	wait_for_children();  // Attendre que tous les enfants terminent
}

void wait_for_children()
{
	int status;

	while (waitpid(-1, &status, 0) > 0)  // Attendre tous les enfants
	{
		if (WIFEXITED(status))
		{
			// Gestion des processus qui se sont terminés normalement
			int exit_status = WEXITSTATUS(status);
			(void)exit_status;  // On ignore ici les codes de retour
		}
		else if (WIFSIGNALED(status))
		{
			// Gestion des processus tués par un signal (ex: CTRL+C)
			int signal = WTERMSIG(status);
			if (signal == SIGINT)
			{
				write(1, "\n", 1);
			}
		}
	}
}
