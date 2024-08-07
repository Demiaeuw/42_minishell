/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:09:13 by toto              #+#    #+#             */
/*   Updated: 2024/06/11 21:14:11 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	is_builtin(char *value)
{
	if (!ft_strcmp(value, "cd") || !ft_strcmp(value, "/bin/cd")
		|| !ft_strcmp(value, "unset") || !ft_strcmp(value, "export")
		|| !ft_strcmp(value, "exit"))
	{
		return (1);
	}
	return (0);
}

int	is_fork_builtin(char *value)
{
	if (!ft_strcmp(value, "echo") || !ft_strcmp(value, "env")
		|| !ft_strcmp(value, "/bin/env") || !ft_strcmp(value, "/bin/echo")
		|| !ft_strcmp(value, "export") || !ft_strcmp(value, "cd")
		|| !ft_strcmp(value, "pwd") || !ft_strcmp(value, "/bin/cd")
		|| !ft_strcmp(value, "unset"))
	{
		return (1);
	}
	return (0);
}

void	make_pipe(t_command *cmd, t_astnode *node)
{
	if (pipe(cmd->p_id2) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	while (node->inputs->next)
		node->inputs = node->inputs->next;
	write(cmd->p_id2[1], node->inputs->filename,
		ft_strlen(node->inputs->filename));
}

t_command	*init_command(int dupout, int dupin, t_mainstruct mainstruct)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	cmd->std_out = dupout;
	cmd->std_in = dupin;
	cmd->pids = malloc(1024 * sizeof(int));
	cmd->pid_count = 0;
	cmd->here_doc = 0;
	cmd->mainstruct = mainstruct;
	return (cmd);
}

void	free_command(t_command *cmd)
{
	int	tmp;
	int	j;

	j = 0;
	while (j < cmd->pid_count)
	{
		waitpid(cmd->pids[j], &tmp, 0);
		j++;
	}
	*cmd->mainstruct.exit_status = my_wexitstatus(tmp);
	free(cmd->pids);
	free(cmd);
}
