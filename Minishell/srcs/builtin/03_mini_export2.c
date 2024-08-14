/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_mini_export2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 00:45:04 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/14 11:50:45 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	process_export_token(t_envp *envp, char *token)
{
	char	*equal_sign;
	char	*var;
	char	*value;

	equal_sign = strchr(token, '=');
	if (!equal_sign)
		return ;
	var = strndup(token, equal_sign - token);
	value = equal_sign + 1;
	if (var && *var)
		add_or_update_env(envp, var, value);
	free(var);
}

void	exe_export(t_envp *envp, char *args)
{
	char	*token;

	if (!args)
		return ;
	if (strncmp(args, "export ", 7) == 0)
		args += 7;
	token = strtok(args, " ");
	while (token != NULL)
	{
		process_export_token(envp, token);
		token = strtok(NULL, " ");
	}
}
