/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 02:35:38 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/27 16:28:16 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Fonction pour gérer la création et l'exécution des processus
void	create_and_handle(t_process_data *args, int *fd_in, int *pipefd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		handle_pipe_child_process(args, pipefd);
	else
		handle_pipe_parent_process(pid, fd_in, pipefd);
}

// Fonction principale de gestion des pipes
void	execute_pipes(t_token *token, t_envp *envp, t_signal *handler)
{
	int				pipefd[2];
	int				fd_in;
	t_process_data	args;

	fd_in = 0;
	args.envp = envp;
	args.handler = handler;
	while (token)
	{
		if (token->type == TOKEN_COMMAND)
		{
			args.token = token;
			create_pipe_if_needed(pipefd, token);
			setup_process_args(&args, fd_in, pipefd);
			create_and_handle(&args, &fd_in, pipefd);
		}
		token = token->next;
	}
}
