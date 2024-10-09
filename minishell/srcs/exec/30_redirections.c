/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 23:45:42 by gaesteve          #+#    #+#             */
/*   Updated: 2024/10/09 18:25:05 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	redirect_outfile(const char *filename, int append)
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
	int fd_in = -1;
	int fd_out = -1;
	t_chevron *current = chevron_list;

	while (current)
	{
		if (current->type == IN)
		{
			fd_in = open(current->value, O_RDONLY);
			if (fd_in == -1)
			{
				perror("Erreur d'ouverture du fichier d'entrée");
				return ;
			}
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		else if (current->type == OUT || current->type == DOUBLE_OUT)
		{
			int flags = O_WRONLY | O_CREAT;
			flags |= (current->type == DOUBLE_OUT) ? O_APPEND : O_TRUNC;
			fd_out = open(current->value, flags, 0644);
			if (fd_out == -1)
			{
				perror("Erreur d'ouverture du fichier de sortie");
				return ;
			}
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
		else if (current->type == DOUBLE_IN)
		{
			fd_in = handle_heredoc(current->value);
			if (fd_in == -1)
			{
				perror("Erreur avec le heredoc");
				return ;
			}
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		current = current->next;
	}
}
