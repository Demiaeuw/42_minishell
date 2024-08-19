/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 02:35:38 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/19 18:26:09 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_pipes(int pipe_fd[2])
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

void	execute_command(t_token *token, t_envp *env, t_signal *handler)
{
	if (token->file_in_out != NULL && token->file_in_out->clean_value != NULL)
		main_command_chevron(token, env, handler);
	else
		main_command(token, env, handler);
}

void	child_process(t_token *current, int fd_in, int pipe_fd[2],
					t_envp *env, t_signal *handler)
{
	if (fd_in != 0)
	{
		if (dup2(fd_in, 0) == -1)
			exit(EXIT_FAILURE);
	}
	if (current->next && current->next->type == TOKEN_PIPE)
	{
		if (dup2(pipe_fd[1], 1) == -1)
			exit(EXIT_FAILURE);
	}
	close_pipes(pipe_fd);
	execute_command(current, env, handler);
	exit(EXIT_FAILURE);
}

void	execute_pipes(t_token *token, t_envp *env, t_signal *handler)
{
	t_token	*current;
	int		pipe_fd[2];
	int		fd_in;
	pid_t	pid;

	fd_in = 0;
	current = token;
	while (current)
	{
		if (current->type == TOKEN_COMMAND)
		{
			if (current->next && current->next->type == TOKEN_PIPE)
			{
				if (pipe(pipe_fd) == -1)
				{
					perror("pipe");
					return ;
				}
			}
			pid = fork();
			if (pid == -1)
			{
				perror("fork");
				return ;
			}
			if (pid == 0)
				child_process(current, fd_in, pipe_fd, env, handler);
			else
			{
				waitpid(pid, NULL, 0);
				close(pipe_fd[1]);
				fd_in = pipe_fd[0];
			}
		}
		current = current->next;
		if (current && current->type == TOKEN_PIPE)
			current = current->next;
	}
}

