/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_builtinexe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:13:41 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/08 16:23:37 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	main_builtin(t_token *token, t_envfinal *env)
{
	t_token *current;

	current = token;
	while (current != NULL)
	{
		if (current->type == TOKEN_COMMAND || current->type == TOKEN_PIPE)
		{
			if (builtin_check(current))
				builtin_selector(current, env);
			else
				execute_execve(current); // a faire la fonction exeve
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
	(void)env;
	// if (ft_strcmp("cd", token->builtin_info) == 0)
	// 	exe_cd(token->value, env->???????);
	if (ft_strcmp("echo", token->builtin_info) == 0)
		exe_echo(token->value);
	else if (ft_strcmp("env", token->builtin_info) == 0)
		mini_env(env);
	// else if (ft_strcmp("export", token->builtin_info) == 0)
	// 	mini_export(token->value, env->?????)
	// else if (ft_strcmp("unset", token->builtin_info) == 0)
	// 	mini_unset(token->value, env->???????);
	else if (ft_strcmp("pwd", token->builtin_info) == 0)
		exe_pwd();
	else if (ft_strcmp("exit", token->builtin_info) == 0)
	 	exe_exit(token->value, env, token);
	else
		printf("else nique ta reum\n");
}

void	execute_execve(t_token *token)
{
	(void)token;
	printf("ce n'est pas un builtin\n");
}
