/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_exec_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 23:40:12 by gaesteve          #+#    #+#             */
/*   Updated: 2024/08/17 23:43:20 by gaesteve         ###   ########.fr       */
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

void	handle_signals_in_parent(t_signal *handler)
{
	if (handler->sigint)
	{
		write(1, "\n", 1);
		handler->sigint = 0;
	}
	if (handler->sigquit)
	{
		write(1, "Quit: 3\n", 8);
		handler->sigquit = 0;
	}
}

void	cleanup_execution(char **split_args, char **args, char *cmd_path)
{
	free(split_args);
	free(args);
	free(cmd_path);
}
