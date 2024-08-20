/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_exec_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 23:13:05 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/20 15:19:24 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_memory_error(char **split_args, char **args)
{
	perror("Memory allocation failed");
	if (split_args)
		free(split_args);
	if (args)
		free(args);
}

void	execute_child_process(char *ch, char **split_args, t_envp *envp)
{
	if (execve(ch, split_args, envp->env) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

int	prepare_command(char ***split_args, char ***args, t_token *token)
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

int	prepare_execution(char **split_args, char **args, char **cmd_path)
{
	*cmd_path = get_command_path(split_args[0]);
	if (!*cmd_path)
	{
		write(2, "Command not found: ", 19);
		write(2, split_args[0], strlen(split_args[0]));
		write(2, "\n", 1);
		handle_memory_error(split_args, args);
		return (0);
	}
	return (1);
}

// void	execute_execve(t_token *token, t_envp *envp, t_signal *handler)
// {
// 	pid_t	pid;
// 	int		status;
// 	char	**args;
// 	char	*cmd_path;
// 	char	**split_args;

// 	if (!prepare_command(&split_args, &args, token))
// 		return ;
// 	if (!prepare_execution(split_args, args, &cmd_path))
// 		return ;
// 	pid = fork_and_execute(cmd_path, split_args, envp);
// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		handle_memory_error(split_args, args);
// 		return ;
// 	}
// 	else
// 	{
// 		waitpid(pid, &status, 0);
// 		handle_signals_in_parent(handler);
// 	}
// 	cleanup_execution(split_args, args, cmd_path);
// }

// void	execute_execve(t_token *token, t_envp *envp, t_signal *handler)
// {
// 	pid_t	pid;
// 	int		status;
// 	char	**args;
// 	char	*cmd_path;
// 	char	**split_args;

// 	// Préparer la commande et les arguments
// 	if (!prepare_command(&split_args, &args, token))
// 		return ;
// 	if (!prepare_execution(split_args, args, &cmd_path))
// 		return ;

// 	// Créer un processus enfant
// 	pid = fork();
// 	if (pid == -1)  // Si le fork échoue
// 	{
// 		perror("fork");
// 		handle_memory_error(split_args, args);
// 		return ;
// 	}
// 	else if (pid == 0)  // Processus enfant
// 	{
// 		printf("Child process created: PID = %d\n", getpid());  // Debugging

// 		// Réinitialiser les gestionnaires de signaux dans le processus enfant
// 		signal(SIGINT, SIG_DFL);  // Rétablir le comportement par défaut de SIGINT
// 		signal(SIGTERM, SIG_DFL); // Rétablir le comportement par défaut de SIGTERM

// 		// Appliquer les redirections dans le processus enfant
// 		handle_redirections(token);
// 		printf("Redirections applied in child process\n");  // Debugging

// 		printf("Child process about to execute command: %s\n", cmd_path);
// 		if (execve(cmd_path, split_args, envp->env) == -1)
// 		{
// 			perror("execve");
// 			exit(EXIT_FAILURE);
// 		}

// 		// Ce code ne sera jamais atteint si execve réussit, mais par précaution :
// 		close(STDIN_FILENO);
// 		exit(EXIT_FAILURE);
// 	}
// 	else  // Processus parent
// 	{
// 		printf("Parent process waiting for PID = %d\n", pid);  // Debugging
// 		waitpid(pid, &status, 0);  // Attendre la fin du processus enfant
// 		printf("Child process with PID = %d finished\n", pid);  // Debugging
// 		handle_signals_in_parent(handler);
// 	}

// 	// Nettoyer les ressources utilisées
// 	cleanup_execution(split_args, args, cmd_path);
// }

void execute_execve(t_token *token, t_envp *envp, t_signal *handler)
{
    pid_t pid;
    int status;
    char **args;
    char *cmd_path;
    char **split_args;

    // Préparer la commande et les arguments
    if (!prepare_command(&split_args, &args, token))
        return;
    if (!prepare_execution(split_args, args, &cmd_path))
        return;

    // Créer un processus enfant
    pid = fork();
    if (pid == -1)  // Si le fork échoue
    {
        perror("fork");
        handle_memory_error(split_args, args);
        return;
    }
    else if (pid == 0)  // Processus enfant
    {
        printf("Child process created: PID = %d\n", getpid());  // Debugging

        // Réinitialiser les gestionnaires de signaux dans le processus enfant
        signal(SIGINT, SIG_DFL);  // Rétablir le comportement par défaut de SIGINT
        signal(SIGTERM, SIG_DFL); // Rétablir le comportement par défaut de SIGTERM

        // Appliquer les redirections dans le processus enfant
        handle_redirections(token);
        printf("Redirections applied in child process\n");  // Debugging

        // Test supplémentaire : vérifier si stdin est lu correctement
        char buffer[1024];
        ssize_t bytes_read;

        printf("Attempting to read from stdin after redirection...\n");
        bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
        if (bytes_read > 0)
        {
            buffer[bytes_read] = '\0'; // Terminez la chaîne lue
            printf("Read from stdin before execve: %s\n", buffer);
        }
        else if (bytes_read == 0)
        {
            printf("EOF reached on stdin before execve\n");
        }
        else
        {
            perror("read from stdin before execve");
        }

        // Exécuter la commande
        printf("Child process about to execute command: %s\n", cmd_path);
        if (execve(cmd_path, split_args, envp->env) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }

        // Ce code ne sera jamais atteint si execve réussit, mais par précaution :
        close(STDIN_FILENO);
        exit(EXIT_FAILURE);
    }
    else  // Processus parent
    {
        printf("Parent process waiting for PID = %d\n", pid);  // Debugging
        waitpid(pid, &status, 0);  // Attendre la fin du processus enfant
        printf("Child process with PID = %d finished\n", pid);  // Debugging
        handle_signals_in_parent(handler);
    }

    // Nettoyer les ressources utilisées
    cleanup_execution(split_args, args, cmd_path);
}
