/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_exec_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 23:40:12 by gaesteve          #+#    #+#             */
/*   Updated: 2024/08/27 15:29:13 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cleanup_execution(char **split_args, char **args, char *cmd_path)
{
	if (split_args)
		free_split_command(split_args);
	if (args)
		free_split_command(args);
	if (cmd_path)
		free(cmd_path);
}

void	file_descriptor_handler(int in, int out)
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

void	handle_parent_process(pid_t pid, t_signal *handler)
{
	waitpid(pid, &handler->sigterm, WUNTRACED);
	handle_signals_in_parent(handler);
	if (WIFSIGNALED(handler->sigterm))
		handler->sigterm = WTERMSIG(handler->sigterm) + 128;
	else if (WIFEXITED(handler->sigterm))
		handler->sigterm = WEXITSTATUS(handler->sigterm);
}

void	handle_child_process(t_process_data *args)
{
	file_descriptor_handler(args->in, args->out);
	handle_redirections(args->token->file_in_out);
	execute_execve(args->token, args->envp, args->handler);
	exit(EXIT_FAILURE);
}

void	create_child_process(t_process_data *args)
{
	pid_t	pid;

	if (builtin_check(args->token))
		builtin_selector_chevron(args->token, args->envp);
	else
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork error");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
			handle_child_process(args);
		else
			handle_parent_process(pid, args->handler);
	}
}
