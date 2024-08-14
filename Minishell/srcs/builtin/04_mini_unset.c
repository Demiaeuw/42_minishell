/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_mini_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:55:21 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/14 01:24:52 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exe_unset(t_envp *envp, char *args)
{
	char	*var;

	var = args;
	if (strncmp(var, "unset ", 6) == 0)
		var += 6;
	if (*var)
		unset_variable(envp, var);
}

void	unset_variable(t_envp *envp, const char *var)
{
	int	i;
	int	j;
	int	var_len;

	i = 0;
	var_len = ft_strlen(var);
	while (envp->env[i])
	{
		if (ft_strncmp(envp->env[i], var, var_len) == 0
			&& envp->env[i][var_len] == '=')
		{
			free(envp->env[i]);
			j = i;
			while (envp->env[j])
			{
				envp->env[j] = envp->env[j + 1];
				j++;
			}
			return ;
		}
		i++;
	}
}
