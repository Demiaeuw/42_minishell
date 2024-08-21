/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_exec_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 23:40:12 by gaesteve          #+#    #+#             */
/*   Updated: 2024/08/21 17:27:39 by gaesteve         ###   ########.fr       */
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
