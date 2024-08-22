/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_exec_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 23:13:05 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/23 00:55:23 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_memory_error(char **split_args, char **args)
{
	if (split_args)
		free(split_args);
	if (args)
		free(args);
}
//debogage dans cette fonction
void execute_child_process(char *cmd_path, char **split_args, t_envp *envp)
{
	printf("Chemin de la commande: %s\n", cmd_path);
	for (int i = 0; split_args[i] != NULL; i++)
	{
		printf("Argument %d: %s\n", i, split_args[i]);
	}
	if (execve(cmd_path, split_args, envp->env) == -1)
	{
		perror("execve error");
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
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		handle_memory_error(split_args, args);
		return ;
	}
	else if (pid == 0)
		execute_child_process(cmd_path, split_args, envp);
	else
	{
		waitpid(pid, &status, 0);
		handle_signals_in_parent(handler);
	}
	cleanup_execution(split_args, args, cmd_path);
}
