/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   31_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:04:57 by gaesteve          #+#    #+#             */
/*   Updated: 2024/08/27 15:39:36 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_heredoc_input(int pipefd[2], char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
}

void	handle_heredoc(char *delimiter)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return ;
	}
	handle_heredoc_input(pipefd, delimiter);
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2 (heredoc redirection)");
		close(pipefd[0]);
		return ;
	}
	close(pipefd[0]);
}
