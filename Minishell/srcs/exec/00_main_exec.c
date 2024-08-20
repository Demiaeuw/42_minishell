/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 02:39:17 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/20 01:19:08 by acabarba         ###   ########.fr       */
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
	else if (token->file_in_out != NULL && token->file_in_out->value != NULL)
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
	handle_all_heredocs(token);  // Gérer tous les heredocs d'abord
	remove_heredoc_chevrons(token); // Supprimer les chevrons heredoc avant l'exécution

	t_token	*current = token;
	int		saved_stdin = dup(STDIN_FILENO);
	int		saved_stdout = dup(STDOUT_FILENO);
	
	while (current != NULL)
	{
		if (current->type == TOKEN_COMMAND || current->type == TOKEN_PIPE)
		{
			printf("Before redirections: cmd = %s\n", current->value);  // Debugging
			handle_redirections(current);  // Appliquer les redirections (hors heredocs)
			
			if (builtin_check(current))
			{
				printf("Executing builtin: %s\n", current->value);  // Debugging
				builtin_selector_chevron(current, envp);
			}
			else
			{
				printf("Executing command: %s\n", current->value);  // Debugging
				execute_execve(current, envp, handler);
			}
			
			dup2(saved_stdin, STDIN_FILENO);  // Restaurer stdin après exécution
			dup2(saved_stdout, STDOUT_FILENO);  // Restaurer stdout après exécution
		}
		current = current->next;
	}
	
	close(saved_stdin);
	close(saved_stdout);
}

