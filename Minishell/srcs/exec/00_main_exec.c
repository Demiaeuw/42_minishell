/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 02:39:17 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/10 03:02:21 by acabarba         ###   ########.fr       */
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
		main_builtin(token, env);
}
