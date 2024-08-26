/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_handle_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 23:45:42 by gaesteve          #+#    #+#             */
/*   Updated: 2024/08/26 21:55:17 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	open_infile(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	return (fd);
}

int	open_outfile(char *filename, int flags)
{
	int	fd;

	fd = open(filename, flags, 0644);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	return (fd);
}

int	redirect_infile(char *filename)
{
	int fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open (input file)");
		return -1;
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2 (input redirection)");
		close(fd);
		return -1;
	}
	close(fd);
	return 0;
}

int	redirect_outfile(char *filename, int append)
{
	int flags = O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC);
	int fd = open(filename, flags, 0644);
	if (fd < 0)
	{
		perror("open (output file)");
		return -1;
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2 (output redirection)");
		close(fd);
		return -1;
	}
	close(fd);
	return 0;
}
//EN COURS
//pipefd c est un tableau de descripteur de fichier en gros.
//pipefd0 c est pour la lecture depuis le pipe
//pipefd1 c est pour l ecrite dans le pipe
void	handle_heredoc(char *delimiter)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return ;
	}
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
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2 (heredoc redirection)");
		close(pipefd[0]);
		return ;
	}
	close(pipefd[0]);
}

void	handle_redirections(t_chevron *chevron_list)
{
	t_chevron *current = chevron_list;
	while (current)
	{
		if (current->type == IN)
			redirect_infile(current->value);
		else if (current->type == OUT)
			redirect_outfile(current->value, 0);
		else if (current->type == DOUBLE_OUT)
			redirect_outfile(current->value, 1);
		else if (current->type == DOUBLE_IN)
			handle_heredoc(current->value);
		current = current->next;
	}
}
