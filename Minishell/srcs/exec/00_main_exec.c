/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 02:39:17 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/10 21:45:42 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	main_exec(t_token *token, t_envfinal *env)
{
	t_token *current;
	int		pipe;

	current = token;
	pipe = 0;
	while (current)
	{
		if (current->type == TOKEN_PIPE)
			pipe = 1;
		current = current->next;
	}
	if (pipe == 1)
		execute_pipes(token, env);
	else
		main_command(token, env);
}

void	main_command(t_token *token, t_envfinal *env)
{
	t_token	*current;

	current = token;
	while (current != NULL)
	{
		if (current->type == TOKEN_COMMAND || current->type == TOKEN_PIPE)
		{
			if (builtin_check(current))
				builtin_selector(current, env);
			else
				other_command(current, env);
		}
		current = current->next;
	}
}

void	other_command(t_token *token, t_envfinal *env)
{
	char	**envarray;
	//test
	if (ft_strcmp(token->builtin_info, "ls") == 0)
		exe_ls();
	//fin de test
	else if (!ft_strcmp("./minishell", token->value))
	{
		envarray = convert_env(env);
		launch_minishell(envarray);
		return ;
	}
	else if (!ft_strcmp("clear", token->builtin_info))
        exe_clear();
	else 
		execute_execve(token, env);
}