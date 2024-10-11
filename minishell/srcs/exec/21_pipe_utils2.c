/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21_pipe_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpourcel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:58:37 by kpourcel          #+#    #+#             */
/*   Updated: 2024/10/10 11:59:04 by kpourcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	process_heredoc_redirection(t_process_data *args, int *fd_in)
{
	int	heredoc_fd;

	if (args->token->file_in_out && args->token->file_in_out->type == DOUBLE_IN)
	{
		heredoc_fd = handle_heredoc(args->token->file_in_out->value);
		if (heredoc_fd != -1)
			*fd_in = heredoc_fd;
	}
}

void	setup_child_execution(int *fd_in, int *pipefd, t_process_data *args)
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
		handle_redirections(args->token->file_in_out);
	if (builtin_check(args->token))
		builtin_selector(args->token, args->envp);
	else
		execute_execve(args->token, args->envp, args->handler);
}

void	process_parent_actions(int *fd_in, int *pipefd, pid_t pid,
	pid_t *last_pid)
{
	if (*fd_in != 0)
		close(*fd_in);
	if (pipefd[1] != -1)
		close(pipefd[1]);
	*fd_in = pipefd[0];
	*last_pid = pid;
}

void	handle_p(t_process_data *args, int *fd_in, int *pipefd, pid_t *last_pid)
{
	pid_t	pid;

	process_heredoc_redirection(args, fd_in);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		setup_child_execution(fd_in, pipefd, args);
		exit(EXIT_FAILURE);
	}
	else
	{
		process_parent_actions(fd_in, pipefd, pid, last_pid);
	}
}
