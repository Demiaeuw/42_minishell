/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 02:35:38 by acabarba          #+#    #+#             */
/*   Updated: 2024/09/27 21:06:55 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Fonction principale de gestion des pipes
void execute_pipes(t_token *token, t_envp *envp, t_signal *handler)
{
	int pipefd[2];
	int fd_in;
	pid_t last_pid;
	t_process_data args;

	fd_in = 0;
	last_pid = 0;
	args.envp = envp;
	args.handler = handler;
	g_status_cmd = 1;
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
	wait_for_children();
	g_status_cmd = 0;
}
