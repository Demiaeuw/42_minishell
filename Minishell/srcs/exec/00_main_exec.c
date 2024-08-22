/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 02:39:17 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/23 00:53:15 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	main_exec(t_token *token, t_envp *envp, t_signal *handler)
{
	t_token	*current;
	int		pipe;
	int		redirection;

	current = token;
	pipe = 0;
	redirection = 0;
	while (current)
	{
		if (current->type == TOKEN_PIPE)
		{
			pipe = 1;
			break;
		}
		else if (current->file_in_out != NULL)
			redirection = 1;
		current = current->next;
	}
	if (pipe == 1)
		execute_pipes(token, envp, handler);
	else if (redirection == 1)
		main_command_chevron(token, envp, handler);
	else
		main_command(token, envp, handler);
}

void	main_command(t_token *token, t_envp *envp, t_signal *handler)
{
	t_token	*current;

	current = token;
	while (current != NULL)
	{
		if (current->type == TOKEN_COMMAND || current->type == TOKEN_PIPE)
		{
			if (builtin_check(current))
				builtin_selector(current, envp);
			else
				execute_execve(current, envp, handler);
		}
		current = current->next;
	}
}

void	main_command_chevron(t_token *token, t_envp *envp, t_signal *handler)
{
	int		saved_stdin = dup(STDIN_FILENO);
	int		saved_stdout = dup(STDOUT_FILENO);

	handle_redirections(token->file_in_out);
	t_token	*current = token;
	while (current != NULL)
	{
		if (current->type == TOKEN_COMMAND || current->type == TOKEN_PIPE)
		{
			create_child_process(current, envp, handler, saved_stdin, saved_stdout);
			dup2(saved_stdin, STDIN_FILENO);
			dup2(saved_stdout, STDOUT_FILENO);
		}
		current = current->next;
	}
	close(saved_stdin);
	close(saved_stdout);
}
