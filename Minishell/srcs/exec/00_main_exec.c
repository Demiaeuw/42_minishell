/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 02:39:17 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/11 14:36:24 by yonieva          ###   ########.fr       */
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
			{	
				process_token_values(token, env);
				builtin_selector(current, env);
			}
			else
				other_command(current, env);
		}
		current = current->next;
	}
}

void	other_command(t_token *token, t_envfinal *env)
{
	char	**envarray;
	// char	**tokenarray;

	envarray = convert_env(env);
	// tokenarray = convert_token(token);
	if (!ft_strcmp("./minishell", token->value))
	{
		launch_minishell(envarray);
		return ;
	}
	else if (!ft_strcmp("clear", token->builtin_info))
        exe_clear();
	else 
		execute_execve(token, env);
}