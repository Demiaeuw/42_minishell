/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_exec_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 23:13:05 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/17 23:42:34 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_memory_error(char **split_args, char **args)
{
	perror("Memory allocation failed");
	if (split_args)
		free(split_args);
	if (args)
		free(args);
}

static void	execute_child_process(char *ch, char **split_args, t_envp *envp)
{
	if (execve(ch, split_args, envp->env) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

static int	prepare_command(char ***split_args, char ***args, t_token *token)
{
	*split_args = split_command(token->value);
	if (!*split_args)
		return (0);
	*args = convert_token(token);
	if (!*args)
	{
		handle_memory_error(*split_args, NULL);
		return (0);
	}
	return (1);
}

static int	prepare_execution(char **split_args, char **args, char **cmd_path)
{
	*cmd_path = get_command_path(split_args[0]);
	if (!*cmd_path)
	{
		fprintf(stderr, "Command not found: %s\n", split_args[0]);
		handle_memory_error(split_args, args);
		return (0);
	}
	return (1);
}

void	execute_execve(t_token *token, t_envp *envp, t_signal *handler)
{
	pid_t	pid;
	int		status;
	char	**args;
	char	*cmd_path;
	char	**split_args;

	if (!prepare_command(&split_args, &args, token))
		return ;
	if (!prepare_execution(split_args, args, &cmd_path))
		return ;
	pid = fork_and_execute(cmd_path, split_args, envp);
	if (pid == -1)
	{
		perror("fork");
		handle_memory_error(split_args, args);
		return ;
	}
	else
	{
		waitpid(pid, &status, 0);
		handle_signals_in_parent(handler);
	}
	cleanup_execution(split_args, args, cmd_path);
}

// void	execute_execve(t_token *token, t_envp *envp, t_signal *handler)
// {
// 	pid_t pid;
// 	int status;
// 	char **args;
// 	char *cmd_path;
// 	char **split_args;

// 	if (!prepare_command(&split_args, &args, token))
// 		return;
// 	if (!prepare_execution(split_args, args, &cmd_path))
// 		return;

// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		handle_memory_error(split_args, args);
// 		return;
// 	}
// 	if (pid == 0)
// 	{
// 		signal(SIGINT, SIG_DFL);
// 		signal(SIGQUIT, SIG_DFL);
// 		signal(SIGTERM, SIG_DFL);
// 		execute_child_process(cmd_path, split_args, envp);
// 	}
// 	else
// 	{
// 		waitpid(pid, &status, 0);

// 		// Traiter les signaux après l'exécution de la commande
// 		if (handler->sigint)
// 		{
// 			write(1, "\n", 1); // Ajoute une nouvelle ligne après le Ctrl-C
// 			handler->sigint = 0; // Réinitialiser le flag SIGINT
// 		}
// 		if (handler->sigquit)
// 		{
// 			write(1, "Quit: 3\n", 8);
// 			handler->sigquit = 0; // Réinitialiser le flag SIGQUIT
// 		}
// 	}

// 	free(split_args);
// 	free(args);
// 	free(cmd_path);
// }
