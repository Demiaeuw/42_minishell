/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 02:35:38 by acabarba          #+#    #+#             */
/*   Updated: 2024/09/30 11:09:18 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	g_global_sig = 1;
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
		if (token && token->type == TOKEN_PIPE)
			token = token->next;
	}
	wait_for_children();
	g_global_sig = 0;
}
