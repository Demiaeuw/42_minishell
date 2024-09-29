/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   31_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 01:43:00 by gaesteve          #+#    #+#             */
/*   Updated: 2024/09/29 15:47:43 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_heredoc_input(int pipefd[2], char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)  // CTRL+D ou fin de fichier
			break;
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		write(pipefd[1], line, strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);  // Fermer le pipe d'écriture après l'input
}

void	handle_heredoc(char *delimiter)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return;
	}
	g_shell_mode = 2;  // Mode heredoc
	handle_heredoc_input(pipefd, delimiter);  // Lire le heredoc
	// Si interrompu par SIGINT, sortir proprement
	// if (g_shell_mode == 0)
	// {
	// 	close(pipefd[0]);
	// 	return;
	// }
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2 (heredoc redirection)");
		close(pipefd[0]);
	}
	close(pipefd[0]);
	g_shell_mode = 0;
}
