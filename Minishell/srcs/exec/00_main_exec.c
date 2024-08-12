/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 02:39:17 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/12 16:02:31 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	main_exec(t_token *token, char **env)
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

void	main_command(t_token *token, char **env)
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

void	other_command(t_token *token, char **env)
{
	// char	**tokenarray;

	// tokenarray = convert_token(token);
	if (!ft_strcmp("./minishell", token->value))
	{
		launch_minishell(env);
		return ;
	}
	else if (!ft_strcmp("clear", token->builtin_info))
        exe_clear();
	else
	{
		printf("execve normalement");
		//execute_execve(token, env);
	}
}
