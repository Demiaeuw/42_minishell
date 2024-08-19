/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 02:35:38 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/19 20:02:17 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void execute_pipes(t_token *token, t_envp *envp, t_signal *handler)
{
	int		pipefd[2];
	pid_t	pid;
	int		fd_in; // Ce sera l'entrée pour le prochain processus

	fd_in = 0;
	while (token)
	{
		// Si le token est une commande
		if (token->type == TOKEN_COMMAND)
		{
			// Créer un pipe
			if (token->next && token->next->type == TOKEN_PIPE)
			{
				if (pipe(pipefd) == -1)
				{
					perror("pipe");
					exit(EXIT_FAILURE);
				}
			}
			// Forker un processus
			pid = fork();
			if (pid == -1)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
			else if (pid == 0) // Processus enfant
			{
				// Si ce n'est pas la première commande, on redirige l'entrée
				if (fd_in != 0)
				{
					dup2(fd_in, 0);
					close(fd_in);
				}
				// Si ce n'est pas la dernière commande, on redirige la sortie
				if (token->next && token->next->type == TOKEN_PIPE)
				{
					close(pipefd[0]);
					dup2(pipefd[1], 1);
					close(pipefd[1]);
				}
				// Exécuter la commande (gérer les builtins et execve)
				if (builtin_check(token))
					builtin_selector(token, envp);
				else
					execute_execve(token, envp, handler);

				exit(EXIT_SUCCESS);
			}
			else // Processus parent
			{
				// Attendre que l'enfant se termine
				waitpid(pid, NULL, 0);
				// Fermer le pipe
				if (fd_in != 0)
					close(fd_in);
				if (token->next && token->next->type == TOKEN_PIPE)
				{
					close(pipefd[1]);
					fd_in = pipefd[0]; // Sauvegarder l'entrée pour le prochain processus
				}
			}
		}
		// Passer au prochain token
		token = token->next;
	}
}
