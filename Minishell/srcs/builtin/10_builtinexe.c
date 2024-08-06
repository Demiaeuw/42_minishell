/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_builtinexe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:13:41 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/06 14:31:28 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	main_builtin(t_token *token)
{
	t_token *current;

	current = token;
	while (current != NULL)
	{
		if (current->type == TOKEN_COMMAND || current->type == TOKEN_PIPE)
		{
			if (builtin_check(current))
				builtin_selector(current);
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

void	builtin_selector(t_token *token)
{
	if (ft_strcmp("cd", token->builtin_info) == 0)
		exe_cd(token->value, );
	else if (ft_strcmp("echo", token->builtin_info) == 0)
		exe_echo(token->value, );
	else if (ft_strcmp("env", token->builtin_info) == 0)
		mini_env(token->value, );
	else if (ft_strcmp("export", token->builtin_info) == 0)
		?????
	else if (ft_strcmp("unset", token->builtin_info) == 0)
		mini_unset(token->value, );
	else if (ft_strcmp("pwd", token->builtin_info) == 0)
		exe_pwd(token->value, );
	else if (ft_strcmp("exit", token->builtin_info) == 0)
		exe_exit(token->value, );
}
