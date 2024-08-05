/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:15:53 by toto              #+#    #+#             */
/*   Updated: 2024/06/11 21:06:16 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	**execute_commande_split(t_astnode *node, int *exit_status,
		int *here_doc, t_command *cmd)
{
	char	**split_nodevalue;

	if (node->inputs)
		*here_doc = redirection_in(node, exit_status, cmd);
	else
		*here_doc = 0;
	if (*here_doc == 2)
		return (NULL);
	replaceenvvars(&node->value, *(cmd->mainstruct.env), exit_status);
	split_nodevalue = ft_split(node->value, ' ');
	split_nodevalue = check_wildcard(split_nodevalue);
	split_nodevalue = clean_quote_all(split_nodevalue);
	if (split_nodevalue[0] == NULL)
	{
		ft_putendl_fd("minishell: : command not found", 2);
		return (NULL);
	}
	if (is_builtin(clean_quote(split_nodevalue[0])))
	{
		if (!execute_builtin(cmd, split_nodevalue, node))
		{
			return (NULL);
		}
	}
	return (split_nodevalue);
}

void	execute_command2(t_astnode *node, t_command *cmd,
		char **split_nodevalue, pid_t pid)
{
	if (pid == 0)
	{
		handle_child_process(node, cmd);
		if (is_fork_builtin(clean_quote(split_nodevalue[0])))
			execute_fork_builtin(*(cmd->mainstruct.env),
				*(cmd->mainstruct.export), split_nodevalue);
		execute(split_nodevalue, get_path(*(cmd->mainstruct.env)),
			*(cmd->mainstruct.env));
	}
	else
	{
		handle_parent_process(node, cmd);
		cmd->pids[cmd->pid_count] = pid;
		(cmd->pid_count)++;
		free_tab(split_nodevalue);
	}
}

void	execute_command(t_astnode *node, t_command *cmd)
{
	char	**split_nodevalue;
	char	*value;
	pid_t	pid;

	if (node == NULL || node->value == NULL)
		return ;
	value = node->value;
	if (pipe(cmd->p_id) == -1)
		return ((void)perror("pipe"), (void)exit(EXIT_FAILURE));
	if (cmd->fd == -1)
		cmd->fd = cmd->p_id[1];
	split_nodevalue = execute_commande_split(node, cmd->mainstruct.exit_status,
			&(cmd->here_doc), cmd);
	if (split_nodevalue == NULL)
		return ;
	pid = fork();
	if (pid == -1)
		return ((void)perror("fork"), (void)exit(EXIT_FAILURE));
	execute_command2(node, cmd, split_nodevalue, pid);
	if (ft_strcmp(value, node->value) != 0)
		free(node->value);
}

void	execute_output_append_command(t_astnode *node, t_command *cmd)
{
	t_redirection	*tmp;

	if (node->outputs)
	{
		while (node->outputs->next)
		{
			tmp = node->outputs;
			node->outputs = node->outputs->next;
			free(tmp);
		}
		cmd->fd = open_output_append(node);
		if (cmd->fd == -1)
		{
			*cmd->mainstruct.exit_status = 1;
			return ;
		}
		execute_command(node, cmd);
		close(cmd->fd);
	}
	if (!node->is_last_command)
	{
		cmd->fd = -1;
		execute_command(node, cmd);
	}
}
