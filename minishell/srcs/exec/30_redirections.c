/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 23:45:42 by gaesteve          #+#    #+#             */
/*   Updated: 2024/09/27 14:42:46 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int	open_infile(char *filename)
// {
// 	int	fd;

// 	fd = open(filename, O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("open");
// 		return (-1);
// 	}
// 	return (fd);
// }

// int	open_outfile(char *filename, int flags)
// {
// 	int	fd;

// 	fd = open(filename, flags, 0644);
// 	if (fd < 0)
// 	{
// 		perror("open");
// 		return (-1);
// 	}
// 	return (fd);
// }

int	redirect_infile(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open (input file)");
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2 (input redirection)");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	redirect_outfile(char *filename, int append)
{
	int	flags;
	int	fd;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(filename, flags, 0644);
	if (fd < 0)
	{
		perror("open (output file)");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2 (output redirection)");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

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

void	handle_redirections(t_chevron *chevron_list)
{
	t_chevron	*current;

	current = chevron_list;
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
