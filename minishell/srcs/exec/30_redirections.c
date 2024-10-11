/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpourcel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 23:45:42 by gaesteve          #+#    #+#             */
/*   Updated: 2024/10/10 11:43:15 by kpourcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_input_redirection(const char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("Erreur d'ouverture du fichier d'entrée");
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	handle_output_redirection(const char *file, int type)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (type == DOUBLE_OUT)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(file, flags, 0644);
	if (fd == -1)
	{
		perror("Erreur d'ouverture du fichier de sortie");
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	handle_heredoc_redirection(const char *delimiter)
{
	int		fd;
	char	*mutable_delimiter;

	mutable_delimiter = (char *)delimiter;
	fd = handle_heredoc(mutable_delimiter);
	if (fd == -1)
	{
		perror("Erreur avec le heredoc");
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	manage_single_redirection(t_chevron *chevron)
{
	if (chevron->type == IN)
		return (handle_input_redirection(chevron->value));
	else if (chevron->type == OUT || chevron->type == DOUBLE_OUT)
		return (handle_output_redirection(chevron->value, chevron->type));
	else if (chevron->type == DOUBLE_IN)
		return (handle_heredoc_redirection(chevron->value));
	return (0);
}

void	handle_redirections(t_chevron *chevron_list)
{
	t_chevron	*current;

	current = chevron_list;
	while (current)
	{
		if (manage_single_redirection(current) == -1)
			return ;
		current = current->next;
	}
}
