/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:13:41 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/16 14:56:04 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_check(t_token *token)
{
	return (token->is_builtin);
}

void	builtin_selector(t_token *token, t_envp *envp)
{
	if (!ft_strcmp("cd", token->builtin_info))
		exe_cd(token->value, envp);
	if (!ft_strcmp("echo", token->builtin_info))
		exe_echo(token->value);
	else if (!ft_strcmp("env", token->builtin_info))
		mini_env(envp);
	else if (!ft_strcmp("export", token->builtin_info))
		exe_export(envp, token->value);
	else if (!ft_strcmp("unset", token->builtin_info))
		exe_unset(envp, token->value);
	else if (!ft_strcmp("pwd", token->builtin_info))
		exe_pwd();
	else if (!ft_strcmp("exit", token->builtin_info))
		exe_exit(token->value, envp, token);
}

void	builtin_selector_chevron(t_token *token, t_envp *envp)
{
	if (!ft_strcmp("cd", token->builtin_info))
		exe_cd(token->file_in_out->clean_value, envp);
	if (!ft_strcmp("echo", token->builtin_info))
		exe_echo(token->file_in_out->clean_value);
	else if (!ft_strcmp("env", token->builtin_info))
		mini_env(envp);
	else if (!ft_strcmp("export", token->builtin_info))
		exe_export(envp, token->file_in_out->clean_value);
	else if (!ft_strcmp("unset", token->builtin_info))
		exe_unset(envp, token->file_in_out->clean_value);
	else if (!ft_strcmp("pwd", token->builtin_info))
		exe_pwd();
	else if (!ft_strcmp("exit", token->builtin_info))
		exe_exit(token->file_in_out->clean_value, envp, token);
}
