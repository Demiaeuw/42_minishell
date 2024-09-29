/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 23:45:42 by gaesteve          #+#    #+#             */
/*   Updated: 2024/09/29 18:59:15 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	redirect_infile(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Erreur d'ouverture du fichier");
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("Erreur de dup2 (redirection d'entrée)");
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

void	handle_redirections(t_chevron *chevron_list)
{
	t_chevron	*current;

	current = chevron_list;
	while (current)
	{
		if (current->type == IN)
		{
			if (redirect_infile(current->value) == -1)
				return;
		}
		else if (current->type == OUT)
		{
			if (redirect_outfile(current->value, 0) == -1)
				return;
		}
		else if (current->type == DOUBLE_OUT)
		{
			if (redirect_outfile(current->value, 1) == -1)
				return;
		}
		else if (current->type == DOUBLE_IN)
			handle_heredoc(current->value);
		current = current->next;
	}
}
