/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:15:55 by gaesteve          #+#    #+#             */
/*   Updated: 2024/08/27 16:28:13 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to configure process arguments, including redirections
void	setup_process_args(t_process_data *args, int fd_in, int *pipefd)
{
	args->in = fd_in;
	if (args->token->next && args->token->next->type == TOKEN_PIPE)
		args->out = pipefd[1];
	else
		args->out = STDOUT_FILENO;
}

// Fonction pour gérer les descripteurs de fichiers
void	setup_redirections(int fd_in, int fd_out)
{
	if (fd_in != STDIN_FILENO)
	{
		if (dup2(fd_in, STDIN_FILENO) < 0)
		{
			perror("dup2 error for stdin");
			exit(EXIT_FAILURE);
		}
		close(fd_in);
	}
	if (fd_out != STDOUT_FILENO)
	{
		if (dup2(fd_out, STDOUT_FILENO) < 0)
		{
			perror("dup2 error for stdout");
			exit(EXIT_FAILURE);
		}
		close(fd_out);
	}
}

// Fonction pour creer un pipe si necessaire
void	create_pipe_if_needed(int *pipefd, t_token *token)
{
	if (token->next && token->next->type == TOKEN_PIPE)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		pipefd[0] = -1;
		pipefd[1] = -1;
	}
}

// Fonction pour gérer les processus enfants pour les pipes
void	handle_pipe_child_process(t_process_data *args, int *pipefd)
{
	setup_redirections(args->in, args->out);
	if (args->token->next && args->token->next->type == TOKEN_PIPE)
		close(pipefd[0]);
	if (builtin_check(args->token))
		builtin_selector(args->token, args->envp);
	else
		execute_execve(args->token, args->envp, args->handler);
	exit(EXIT_SUCCESS);
}

// Fonction pour gérer les processus parents pour les pipes
void	handle_pipe_parent_process(pid_t pid, int *fd_in, int *pipefd)
{
	waitpid(pid, NULL, 0);
	if (*fd_in != 0)
		close(*fd_in);
	if (pipefd[1] != -1)
		close(pipefd[1]);
	*fd_in = pipefd[0];
}
