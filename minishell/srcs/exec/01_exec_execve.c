/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_exec_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 23:13:05 by acabarba          #+#    #+#             */
/*   Updated: 2024/09/24 17:34:25 by acabarba         ###   ########.fr       */
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
			(token->file_in_out != NULL && token->file_in_out->value != NULL &&
				ft_strcmp((*split_args)[i], token->file_in_out->value) == 0))
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

int	prepare_execution(char **split_args, char **args, char **cmd_path, t_envp *envp)
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
	pid_t	pid;
	int		status;
	char	**args;
	char	*cmd_path;
	char	**split_args;

	if (!prepare_command(&split_args, &args, token))
		return ;
	if (!prepare_execution(split_args, args, &cmd_path, envp))
		return ;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		handle_memory_error(split_args, args);
		return ;
	}
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTERM, SIG_DFL);
		execute_child_process(cmd_path, split_args, envp);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			write(1, "\n", 1);  // Avoid duplicate prompts after CTRL+C
			g_status_cmd = 130;  // Update global status for SIGINT interrupt
		}
		handle_signals_in_parent(handler);
	}
	cleanup_execution(split_args, args, cmd_path);
}
