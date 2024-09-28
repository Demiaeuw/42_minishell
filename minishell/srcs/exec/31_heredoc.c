/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   31_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 01:43:00 by gaesteve          #+#    #+#             */
/*   Updated: 2024/09/28 02:52:19 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Gère le signal SIGINT pour le heredoc
void	heredoc_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		close(STDIN_FILENO);
		g_shell_mode = 0;
	}
}

void	setup_heredoc_signals(void)
{
	struct sigaction sa;
	sa.sa_handler = heredoc_signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

void	reset_signals(void)
{
	struct sigaction sa;
	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

void	handle_heredoc_input(int pipefd[2], char *delimiter)
{
	char *line;

	while (1)
	{
		line = readline("> ");
		if (!line || g_shell_mode == 0)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
}

void handle_heredoc(char *delimiter)
{
	int pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return ;
	}
	g_shell_mode = 2;
	setup_heredoc_signals();
	handle_heredoc_input(pipefd, delimiter);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2 (heredoc redirection)");
		close(pipefd[0]);
	}
	close(pipefd[0]);

	g_shell_mode = 0;
	reset_signals();
}
