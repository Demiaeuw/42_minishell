/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 02:39:17 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/22 22:37:06 by gaesteve         ###   ########.fr       */
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

	// Appliquer les redirections avant d'entrer dans la boucle
	handle_redirections(token->file_in_out);

	t_token	*current = token;
	while (current != NULL)
	{
		if (current->type == TOKEN_COMMAND || current->type == TOKEN_PIPE)
		{
			create_child_process(current, envp, handler, saved_stdin, saved_stdout);

			// Restaure les descripteurs après chaque commande exécutée
			dup2(saved_stdin, STDIN_FILENO);
			dup2(saved_stdout, STDOUT_FILENO);
		}
		current = current->next;
	}

	close(saved_stdin);
	close(saved_stdout);
}

// void	main_command_chevron(t_token *token, t_envp *envp, t_signal *handler)
// {
// 	t_token	*current;
// 	int		saved_stdin;
// 	int		saved_stdout;

// 	current = token;
// 	saved_stdin = dup(STDIN_FILENO);
// 	saved_stdout = dup(STDOUT_FILENO);
// 	while (current != NULL)
// 	{
// 		if (current->type == TOKEN_COMMAND || current->type == TOKEN_PIPE)
// 		{
// 			handle_redirections(current->file_in_out);
// 			if (builtin_check(current))
// 				builtin_selector_chevron(current, envp);
// 			else
// 				execute_execve(current, envp, handler);
// 			dup2(saved_stdin, STDIN_FILENO);
// 			dup2(saved_stdout, STDOUT_FILENO);
// 		}
// 		current = current->next;
// 	}
// 	close(saved_stdin);
// 	close(saved_stdout);
// }

void	create_child_process(t_token *token, t_envp *envp, t_signal *handler, int in, int out)
{
	pid_t	pid;

	// Vérifie si c'est un builtin
	if (builtin_check(token))
	{
		builtin_selector_chevron(token, envp);  // Exécute le builtin directement dans le processus parent
	}
	else
	{
		// Crée un processus enfant
		pid = fork();
		if (pid < 0)
		{
			perror("fork error");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			// Enfant : Gère les redirections et exécute la commande
			file_descriptor_handler(in, out);
			execute_execve(token, envp, handler);  // Remplace `execute_command` par `execute_execve`
			exit(EXIT_FAILURE);  // Si execve échoue, le processus enfant doit se terminer
		}
		else
		{
			// Parent : Gère les signaux et attend la fin du processus enfant
			waitpid(pid, &handler->sigterm, WUNTRACED);
			handle_signals_in_parent(handler);

			if (WIFSIGNALED(handler->sigterm))
				handler->sigterm = WTERMSIG(handler->sigterm) + 128;
			else if (WIFEXITED(handler->sigterm))
				handler->sigterm = WEXITSTATUS(handler->sigterm);
		}
	}
}

void file_descriptor_handler(int in, int out)
{
	// Redirection de l'entrée standard (stdin)
	if (in != STDIN_FILENO)
	{
		if (dup2(in, STDIN_FILENO) < 0)  // Redirige stdin vers `in`
		{
			perror("dup2 error in file_descriptor_handler for stdin");
			exit(EXIT_FAILURE);
		}
		close(in);  // Ferme l'ancien descripteur
	}

	// Redirection de la sortie standard (stdout)
	if (out != STDOUT_FILENO)
	{
		if (dup2(out, STDOUT_FILENO) < 0)  // Redirige stdout vers `out`
		{
			perror("dup2 error in file_descriptor_handler for stdout");
			exit(EXIT_FAILURE);
		}
		close(out);  // Ferme l'ancien descripteur
	}
}
