/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   31_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 01:43:00 by gaesteve          #+#    #+#             */
/*   Updated: 2024/10/09 18:25:02 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_heredoc_input(int pipefd[2], char *delimiter)
{
	char	*line;

	signal(SIGINT, handle_sigint_heredoc);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			if (g_global_sig == 130)
				break;
			write(1, "\n", 2);
		}
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

int	handle_heredoc(char *delimiter)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	handle_heredoc_input(pipefd, delimiter);
	close(pipefd[1]);
	return (pipefd[0]);
}

void	handle_sigint_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		close(STDIN_FILENO);
		g_global_sig = 130;
	}
}

void	reset_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
