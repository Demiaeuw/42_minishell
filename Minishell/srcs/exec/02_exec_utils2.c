/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_exec_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 23:40:12 by gaesteve          #+#    #+#             */
/*   Updated: 2024/08/26 20:49:14 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

pid_t	fork_and_execute(char *cmd_path, char **split_args, t_envp *envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTERM, SIG_DFL);
		execute_child_process(cmd_path, split_args, envp);
	}
	return (pid);
}

void	cleanup_execution(char **split_args, char **args, char *cmd_path)
{
	if (split_args)
		free_split_command(split_args);
	if (args)
		free_split_command(args);
	if (cmd_path)
		free(cmd_path);
}

void file_descriptor_handler(int in, int out)
{
	if (in != STDIN_FILENO)
	{
		if (dup2(in, STDIN_FILENO) < 0)
		{
			perror("dup2 error in file_descriptor_handler for stdin");
			exit(EXIT_FAILURE);
		}
		close(in);
	}
	if (out != STDOUT_FILENO)
	{
		if (dup2(out, STDOUT_FILENO) < 0)
		{
			perror("dup2 error in file_descriptor_handler for stdout");
			exit(EXIT_FAILURE);
		}
		close(out);
	}
}

// void	create_child_process(t_token *token, t_envp *envp, t_signal *handler, int in, int out)
// {
// 	pid_t	pid;

// 	if (builtin_check(token))
// 	{
// 		builtin_selector_chevron(token, envp);
// 	}
// 	else
// 	{
// 		pid = fork();
// 		if (pid < 0)
// 		{
// 			perror("fork error");
// 			exit(EXIT_FAILURE);
// 		}
// 		else if (pid == 0)
// 		{
// 			file_descriptor_handler(in, out);
// 			handle_redirections(token->file_in_out);
// 			execute_execve(token, envp, handler);
// 			exit(EXIT_FAILURE);
// 		}
// 		else
// 		{
// 			waitpid(pid, &handler->sigterm, WUNTRACED);
// 			handle_signals_in_parent(handler);
// 			if (WIFSIGNALED(handler->sigterm))
// 				handler->sigterm = WTERMSIG(handler->sigterm) + 128;
// 			else if (WIFEXITED(handler->sigterm))
// 				handler->sigterm = WEXITSTATUS(handler->sigterm);
// 		}
// 	}
// }

/// debogage

void	create_child_process(t_token *token, t_envp *envp, t_signal *handler, int in, int out)
{
	pid_t pid;

	if (builtin_check(token))
	{
		builtin_selector_chevron(token, envp);
	}
	else
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork error");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			file_descriptor_handler(in, out);

			// Gérer toutes les redirections ici, y compris heredoc
			handle_redirections(token->file_in_out);

			// Afficher les arguments de la commande avant l'exécution
			char **cmd_args = split_command(token->value);
			printf("Executing command: %s\n", cmd_args[0]);
			for (int i = 1; cmd_args[i] != NULL; i++) {
				printf("Argument %d: %s\n", i, cmd_args[i]);
			}

			execute_execve(token, envp, handler);
			exit(EXIT_FAILURE);
		}
		else
		{
			waitpid(pid, &handler->sigterm, WUNTRACED);
			handle_signals_in_parent(handler);
			if (WIFSIGNALED(handler->sigterm))
				handler->sigterm = WTERMSIG(handler->sigterm) + 128;
			else if (WIFEXITED(handler->sigterm))
				handler->sigterm = WEXITSTATUS(handler->sigterm);
		}
	}
}
