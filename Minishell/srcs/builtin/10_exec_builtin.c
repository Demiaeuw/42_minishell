/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:13:41 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/12 17:42:43 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_check(t_token *token)
{
	return (token->is_builtin);
}

void	builtin_selector(t_token *token, char **env)
{
	// if (!ft_strcmp("cd", token->builtin_info))
	// 	exe_cd(token, env);
	if (!ft_strcmp("echo", token->builtin_info))
		exe_echo(token->value);
	else if (!ft_strcmp("env", token->builtin_info))
		mini_env(env);
	// else if (!ft_strcmp("export", token->builtin_info))
	// 	exe_export(env, token);
	// else if (!ft_strcmp("unset", token->builtin_info))
	// 	exe_unset(&env, token);
	else if (!ft_strcmp("pwd", token->builtin_info))
		exe_pwd();
	else if (!ft_strcmp("exit", token->builtin_info))
		exe_exit(token->value, env, token);
}
