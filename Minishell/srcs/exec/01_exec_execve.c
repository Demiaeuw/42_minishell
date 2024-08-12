/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_exec_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 23:13:05 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/12 15:58:45 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	execute_execve(t_token *token, t_envfinal *env)
// {
// 	pid_t	pid;
// 	int		status;

// 	char **str = convert_token(token);
// 	char **envp = convert_env(env);

// 	if (!str || !envp)
// 	{
// 		perror("Memory allocation failed");
// 		free(str);
// 		free(envp);
// 		return ;
// 	}
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		free(str);
// 		free(envp);
// 		return ;
// 	}
// 	else if (pid == 0)
// 	{
// 		if (execve(str[0], str, envp) == -1)
// 		{
// 			perror("execve");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	else
// 	{
// 		waitpid(pid, &status, 0);
// 		if (WIFEXITED(status))
// 		{
// 			int exit_status = WEXITSTATUS(status);
// 			printf("Child process exited with status %d\n", exit_status);
// 		}
// 		else if (WIFSIGNALED(status))
// 		{
// 			int signal = WTERMSIG(status);
// 			printf("Child process was terminated by signal %d\n", signal);
// 		}
// 		else
// 		{
// 			printf("Child process terminated abnormally\n");
// 		}
// 	}
// 	free(str);
// 	free(envp);
// }


//----------------------------------------------------------------------------//



// void	execute_execve(t_token *token, char **tokenarray, char **envarray)
// {
// 	pid_t	pid;
// 	int		status;
// 	// char *command_path;

// 	// *command_path = get_command_path(token->builtin_info);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		// Processus enfant : exécute la commande spécifiée
// 		if (execve(get_command_path(token->builtin_info), tokenarray, envarray) == -1)
// 		{
// 			perror("Erreur execve");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	else if (pid < 0)
// 	{
// 		// Échec du fork
// 		perror("Erreur fork");
// 	}
// 	else
// 	{
// 		// Processus parent : attend la fin du processus enfant
// 		waitpid(pid, &status, 0);
// 	}
// 	// free(tableau de tableau de token);
// 	// free(tableau de tableau de env);
// }


//----------------------------------------------------------------------------//

static char	*get_command_path2(char *command)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;

	// Si la commande est déjà un chemin absolu
	if (command[0] == '/' || command[0] == '.')
		return (strdup(command));

	// Récupération de la variable d'environnement PATH
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);

	// Séparation des différents chemins dans PATH
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);

	// Recherche de la commande dans les chemins
	i = 0;
	while (paths[i])
	{
		full_path = malloc(strlen(paths[i]) + strlen(command) + 2);
		if (!full_path)
		{
			free(paths);
			return (NULL);
		}
		strcpy(full_path, paths[i]);
		strcat(full_path, "/");
		strcat(full_path, command);

		// Vérification si le chemin existe et est exécutable
		if (access(full_path, X_OK) == 0)
		{
			free(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free(paths);
	return (NULL);  // Commande introuvable
}

void	execute_execve(t_token *token, char **env)
{
	pid_t	pid;
	int		status;
	char	**args;
	char	**envp;
	char	*cmd_path;

	args = convert_token(token);
	envp = convert_env(env);
	if (!args || !envp)
	{
		perror("Memory allocation failed");
		free(args);
		free(envp);
		return ;
	}

	cmd_path = get_command_path2(args[0]);
	if (!cmd_path)
	{
		fprintf(stderr, "Command not found: %s\n", args[0]);
		free(args);
		free(envp);
		return ;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(args);
		free(envp);
		free(cmd_path);
		return ;
	}
	else if (pid == 0)
	{
		if (execve(cmd_path, args, envp) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		// if (WIFEXITED(status))
		// {
		// 	int exit_status = WEXITSTATUS(status);
		// 	printf("Child process exited with status %d\n", exit_status);
		// }
		// else if (WIFSIGNALED(status))
		// {
		// 	int signal = WTERMSIG(status);
		// 	printf("Child process was terminated by signal %d\n", signal);
		// }
	}

	free(args);
	free(envp);
	free(cmd_path);
}

