/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_exec_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 23:13:05 by acabarba          #+#    #+#             */
/*   Updated: 2024/09/29 18:54:54 by gaesteve         ###   ########.fr       */
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

void	execute_child_process(char *cmd_path, char **split_args, t_envp *envp)
{
	if (execve(cmd_path, split_args, envp->env) == -1)
	{
		perror("execve error");
		exit(EXIT_FAILURE);
	}
}

int	prepare_command(char ***split_args, char ***args, t_token *token)
{
	int	i;

	*split_args = split_command(token->value);
	if (!*split_args)
		return (0);
	i = 0;
	while ((*split_args)[i] != NULL)
	{
		if ((ft_strcmp((*split_args)[i], "<<") == 0) ||
				ft_strcmp((*split_args)[i], "<") == 0)
		{
			(*split_args)[i] = NULL;
			break ;
		}
		i++;
	}
	*args = convert_token(token);
	if (!*args)
	{
		handle_memory_error(*split_args, NULL);
		return (0);
	}
	return (1);
}

int	prepare_exec(char **split_args, char **args, char **cmd_path, t_envp *envp)
{
	*cmd_path = get_command_path(split_args[0], envp);
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
	char	**args;
	char	*cmd_path;
	char	**split_args;

	(void)handler;
	if (!prepare_command(&split_args, &args, token))
		return ;
	if (!prepare_exec(split_args, args, &cmd_path, envp))
		return ;
	fork_and_execute(cmd_path, split_args, envp);
	cleanup_execution(split_args, args, cmd_path);
}
