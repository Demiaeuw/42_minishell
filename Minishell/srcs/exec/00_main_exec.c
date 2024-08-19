/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 02:39:17 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/19 20:00:11 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	main_exec(t_token *token, t_envp *envp, t_signal *handler)
// {
// 	t_token	*current;
// 	int		pipe;

// 	current = token;
// 	pipe = 0;
// 	while (current)
// 	{
// 		if (current->type == TOKEN_PIPE)
// 			pipe = 1;
// 		current = current->next;
// 	}
// 	if (pipe == 1)
// 		execute_pipes(token, envp, handler);
// 	else if (token->file_in_out != NULL
// 		&& token->file_in_out->clean_value != NULL)
// 		main_command_chevron(token, envp, handler);
// 	else
// 		main_command(token, envp, handler);
// }

void main_exec(t_token *token, t_envp *envp, t_signal *handler)
{
	t_token	*current;
	int		pipe;

	current = token;
	pipe = 0;
	while (current)
	{
		if (current->type == TOKEN_PIPE)
		{
			pipe = 1;
			break;
		}
		current = current->next;
	}
	if (pipe == 1)
		execute_pipes(token, envp, handler);
	else if (token->file_in_out != NULL && token->file_in_out->clean_value != NULL)
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
	t_token	*current;
	int		saved_stdin;
	int		saved_stdout;

	current = token;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	while (current != NULL)
	{
		if (current->type == TOKEN_COMMAND || current->type == TOKEN_PIPE)
		{
			handle_redirections(current);
			if (builtin_check(current))
				builtin_selector_chevron(current, envp);
			else
				execute_execve(current, envp, handler);
			dup2(saved_stdin, STDIN_FILENO);
			dup2(saved_stdout, STDOUT_FILENO);
		}
		current = current->next;
	}
	close(saved_stdin);
	close(saved_stdout);
}
