/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:15:55 by gaesteve          #+#    #+#             */
/*   Updated: 2024/10/08 16:44:14 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	wait_for_children(void)
{
	int	status;
	int	exit_status;

	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
			(void)exit_status;
		}
	}
}

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

void	setup_process_args(t_process_data *args, int fd_in, int *pipefd)
{
	args->in = fd_in;
	if (args->token->next && args->token->next->type == TOKEN_PIPE
		&& !args->token->file_in_out)
		args->out = pipefd[1];
	else
		args->out = STDOUT_FILENO;
}

void	execute_child_process(t_process_data *args, int *pipefd)
{
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
	if (pipefd[0] != -1)
		close(pipefd[0]);
	if (args->token->file_in_out)
			handle_redirections(args->token->file_in_out);
	if (builtin_check(args->token))
		builtin_selector(args->token, args->envp);
	else
		execute_execve(args->token, args->envp, args->handler);
	exit(EXIT_FAILURE);
}

void	handle_p(t_process_data *args, int *fd_in, int *pipefd, pid_t *last_pid)
{
	pid_t pid;

	if (args->token->file_in_out && args->token->file_in_out->type == DOUBLE_IN)
	{
		int heredoc_fd = handle_heredoc(args->token->file_in_out->value);
		if (heredoc_fd != -1)
		{
			*fd_in = heredoc_fd;
		}
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (*fd_in != STDIN_FILENO)
		{
			dup2(*fd_in, STDIN_FILENO);
			close(*fd_in);
		}
		if (pipefd[1] != STDOUT_FILENO)
		{
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
		}

		if (pipefd[0] != -1)
			close(pipefd[0]);
		if (args->token->file_in_out && args->token->file_in_out->type != DOUBLE_IN)
		{
			handle_redirections(args->token->file_in_out);
		}
		if (builtin_check(args->token))
			builtin_selector(args->token, args->envp);
		else
			execute_execve(args->token, args->envp, args->handler);

		exit(EXIT_FAILURE);
	}
	else
	{
		if (*fd_in != 0)
			close(*fd_in);
		if (pipefd[1] != -1)
			close(pipefd[1]);
		*fd_in = pipefd[0];
		*last_pid = pid;
	}
}
