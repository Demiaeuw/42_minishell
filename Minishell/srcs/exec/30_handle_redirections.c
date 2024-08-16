/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_handle_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 23:45:42 by gaesteve          #+#    #+#             */
/*   Updated: 2024/08/16 21:18:30 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	open_file(t_chevron *chevron)
{
	int	fd;

	fd = -1;
	if (chevron->type == OUT)
		fd = open(chevron->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (chevron->type == DOUBLE_OUT)
		fd = open(chevron->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (chevron->type == IN)
		fd = open(chevron->file_name, O_RDONLY);
	else if (chevron->type == DOUBLE_IN)
		fd = -1;
	if (fd < 0)
		perror("open_file error");
	return (fd);
}

static void	handle_in_redirection(t_chevron *current, int *fd_in)
{
	if (*fd_in != -1)
		close(*fd_in);
	*fd_in = open_file(current);
	if (*fd_in == -1)
		return ;
	dup2(*fd_in, STDIN_FILENO);
}

static void	handle_out_redirection(t_chevron *current, int *fd_out)
{
	if (*fd_out != -1)
		close(*fd_out);
	*fd_out = open_file(current);
	if (*fd_out == -1)
		return ;
	dup2(*fd_out, STDOUT_FILENO);
}

void	handle_redirections(t_token *token)
{
	t_chevron	*current;
	int			fd_in;
	int			fd_out;

	fd_in = -1;
	fd_out = -1;
	current = token->file_in_out;
	while (current)
	{
		if (current->type == IN || current->type == DOUBLE_IN)
			handle_in_redirection(current, &fd_in);
		else if (current->type == OUT || current->type == DOUBLE_OUT)
			handle_out_redirection(current, &fd_out);
		current = current->next;
	}
}
