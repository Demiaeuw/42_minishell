/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:13:41 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/10 20:19:39 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	main_builtin(t_token *token, t_envfinal *env)
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
				execute_execve(current);
		}
		current = current->next;
	}
}

int	builtin_check(t_token *token)
{
	return (token->is_builtin);
}

void	builtin_selector(t_token *token, t_envfinal *env)
{
	if (ft_strcmp("cd", token->builtin_info) == 0)
		exe_cd(token->value, env);
	else if (ft_strcmp("echo", token->builtin_info) == 0)
	{
		// token->value = expend_variable(token->value, env);
		exe_echo(token->value);
	}
	else if (!ft_strcmp("env", token->builtin_info))
		mini_env(env);
	else if (!ft_strcmp("export", token->builtin_info))
		exe_export(env, token);
	else if (!ft_strcmp("unset", token->builtin_info))
		exe_unset(&env, token);
	else if (!ft_strcmp("pwd", token->builtin_info))
		exe_pwd();
	else if (!ft_strcmp("exit", token->builtin_info))
		exe_exit(token->value, env, token);
	else if (!ft_strcmp("clear", token->builtin_info))
        exe_clear();
	else if (!ft_strcmp("./minishell", token->builtin_info))
		
	else
		printf("c'est un builtin mais tu la pas gerer connard\n");
}

void	execute_execve(t_token *token)
{
	if (ft_strcmp(token->builtin_info, "ls") == 0)
		exe_ls();
	else 
	printf("c'est la merde patron\n");
}
