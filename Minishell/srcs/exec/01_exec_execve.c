/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_exec_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 23:13:05 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/12 21:12:53 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**split_command(const char *cmd)
{
	char	**args;
	int		count;
	int		i;
	char	*cmd_copy;
	char	*token;

	// Compte le nombre de mots dans la commande
	count = 0;
	cmd_copy = strdup(cmd);
	token = strtok(cmd_copy, " ");
	while (token)
	{
		count++;
		token = strtok(NULL, " ");
	}
	free(cmd_copy);

	// Alloue de la mémoire pour les arguments
	args = (char **)malloc((count + 1) * sizeof(char *));
	if (!args)
		return (NULL);

	// Sépare la commande en arguments
	i = 0;
	cmd_copy = strdup(cmd);
	token = strtok(cmd_copy, " ");
	while (token)
	{
		args[i] = strdup(token);
		i++;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
	free(cmd_copy);

	return (args);
}

void	execute_execve(t_token *token, char **env)
{
	pid_t	pid;
	int		status;
	char	**args;
	char	*cmd_path;
	char	**split_args;

	split_args = split_command(token->value);  // Utilisation de la nouvelle fonction
	if (!split_args)
	{
		perror("Memory allocation failed");
		return ;
	}

	args = convert_token(token);  // Convertit les tokens en arguments
	if (!args)
	{
		perror("Memory allocation failed");
		free(split_args);
		return ;
	}

	// Debug: Affiche les arguments de la commande
	printf("Arguments :\n");
	for (int i = 0; split_args[i]; i++)
		printf("split_args[%d]: %s\n", i, split_args[i]);

	cmd_path = get_command_path(split_args[0]);
	if (!cmd_path)
	{
		fprintf(stderr, "Command not found: %s\n", split_args[0]);
		free(split_args);
		free(args);
		return ;
	}

	// Debug: Affiche le chemin de la commande
	printf("Command path: %s\n", cmd_path);

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(split_args);
		free(args);
		free(cmd_path);
		return ;
	}
	else if (pid == 0)
	{
		if (execve(cmd_path, split_args, env) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}

	free(split_args);
	free(args);
	free(cmd_path);
}

// void	execute_execve(t_token *token, char **env)
// {
// 	pid_t	pid;
// 	int		status;
// 	char	**args;
// 	char	*cmd_path;
// 	char	**split_args;

// 	split_args = split_command(token->value);
// 	if (!split_args)
// 	{
// 		perror("Memory allocation failed");
// 		return ;
// 	}
// 	args = convert_token(token);
// 	if (!args)
// 	{
// 		perror("Memory allocation failed");
// 		return ;
// 	}
// 	// Debug: Affiche les arguments de la commande
// 	printf("Arguments :\n");
// 	for (int i = 0; args[i]; i++)
// 		printf("args[%d]: %s\n", i, args[i]);
// 	cmd_path = get_command_path(args[0]);
// 	if (!cmd_path)
// 	{
// 		fprintf(stderr, "Command not found: %s\n", args[0]);
// 		free(args);
// 		return ;
// 	}
// 	// Debug: Affiche le chemin de la commande
// 	printf("Command path: %s\n", cmd_path);
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		free(args);
// 		free(cmd_path);
// 		return ;
// 	}
// 	else if (pid == 0)
// 	{
// 		if (execve(cmd_path, args, env) == -1)
// 		{
// 			perror("execve");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	else
// 	{
// 		waitpid(pid, &status, 0);
// 	}
// 	free(args);
// 	free(cmd_path);
// }

