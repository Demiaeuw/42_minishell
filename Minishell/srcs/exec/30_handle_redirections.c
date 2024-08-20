/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_handle_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 23:45:42 by gaesteve          #+#    #+#             */
/*   Updated: 2024/08/20 01:23:17 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int	open_file_in(t_chevron *chevron)
// {
// 	int	fd;

// 	fd = -1;
// 	if (chevron->type == IN)
// 		fd = open(chevron->file_name, O_RDONLY);
// 	else if (chevron->type == DOUBLE_IN)
// 		fd = -1;
// 	if (fd < 0)
// 		perror("open_file error");
// 	return (fd);
// }

// int	open_file_out(t_chevron *chevron)
// {
// 	int	fd;

// 	fd = -1;
// 	if (chevron->type == OUT)
// 		fd = open(chevron->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	else if (chevron->type == DOUBLE_OUT)
// 		fd = open(chevron->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	if (fd < 0)
// 		perror("open_file error");
// 	return (fd);
// }

// void	handle_in_redirection(t_chevron *current, int *fd_in)
// {
// 	if (*fd_in != -1)
// 		close(*fd_in);
// 	*fd_in = open_file_in(current);
// 	if (*fd_in == -1)
// 		return ;
// 	dup2(*fd_in, STDIN_FILENO);
// }

// void	handle_out_redirection(t_chevron *current, int *fd_out)
// {
// 	if (*fd_out != -1)
// 		close(*fd_out);
// 	*fd_out = open_file_out(current);
// 	if (*fd_out == -1)
// 		return ;
// 	dup2(*fd_out, STDOUT_FILENO);
// }

void	handle_all_heredocs(t_token *token)
{
	t_token		*current_token;
	t_chevron	*current_chevron;
	int			heredoc_fd;
	char		*line;

	current_token = token;
	while (current_token)
	{
		current_chevron = current_token->file_in_out;
		while (current_chevron)
		{
			if (current_chevron->chevron_check && current_chevron->type == DOUBLE_IN)
			{
				heredoc_fd = open("/tmp/heredoc_temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (heredoc_fd == -1)
				{
					perror("open heredoc");
					exit(EXIT_FAILURE);
				}
				printf("Starting heredoc, waiting for delimiter: %s\n", current_chevron->next->value);
				while ((line = readline("> ")) != NULL)
				{
					if (strcmp(line, current_chevron->next->value) == 0)
					{
						free(line);
						break;
					}
					write(heredoc_fd, line, strlen(line));
					write(heredoc_fd, "\n", 1);
					free(line);
				}
				close(heredoc_fd);
				printf("Heredoc written to /tmp/heredoc_temp\n");
			}
			current_chevron = current_chevron->next;
		}
		current_token = current_token->next;
	}
}


void	handle_redirections(t_token *token)
{
	t_chevron	*current;
	int			fd;

	current = token->file_in_out;
	while (current)
	{
		if (current->chevron_check)
		{
			if (current->type == OUT)
			{
				fd = open(current->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd == -1)
					perror("open");
				else
					dup2(fd, STDOUT_FILENO);
			}
			else if (current->type == DOUBLE_OUT)
			{
				fd = open(current->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (fd == -1)
					perror("open");
				else
					dup2(fd, STDOUT_FILENO);
			}
			else if (current->type == IN)
			{
				fd = open(current->next->value, O_RDONLY);
				if (fd == -1)
					perror("open");
				else
					dup2(fd, STDIN_FILENO);
			}
			else if (current->type == DOUBLE_IN)
			{
				fd = open("/tmp/heredoc_temp", O_RDONLY);
				if (fd == -1)
					perror("open heredoc");
				else
				{
					dup2(fd, STDIN_FILENO);  // Rediriger stdin vers le fichier heredoc
					printf("Redirecting stdin from /tmp/heredoc_temp\n");
				}
			}
			close(fd);
		}
		current = current->next;
	}
}



void remove_heredoc_chevrons(t_token *token)
{
	t_chevron *prev = NULL;
	t_chevron *current = token->file_in_out;

	while (current)
	{
		if (current->chevron_check && current->type == DOUBLE_IN)
		{
			// Supprimer le chevron et la valeur suivante
			t_chevron *to_free = current;
			if (prev)
				prev->next = current->next->next;
			else
				token->file_in_out = current->next->next;

			current = current->next->next;

			free(to_free->next->value);
			free(to_free->next);
			free(to_free->value);
			free(to_free);
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}

	// En plus, nettoyer le champ 'value' de 'token' pour supprimer << et end
	if (token->value)
	{
		char *start = strstr(token->value, "<<");
		if (start)
		{
			char *end = strstr(start, " end");
			if (end)
			{
				// Enlever << et end
				memmove(start, end + 4, strlen(end + 4) + 1);
			}
		}
	}
}
