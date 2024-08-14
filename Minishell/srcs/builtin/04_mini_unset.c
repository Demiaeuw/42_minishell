/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_mini_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:55:21 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/14 16:57:37 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exe_unset(t_envp *envp, char *args)
{
	char	**variables;
	int		i;

	i = 0;
	variables = ft_split(args, ' ');
	while (variables[i])
	{
		unset_variable(envp, variables[i]);
		i++;
	}
	i = 0;
	while (variables[i])
	{
		free(variables[i]);
		i++;
	}
	free(variables);
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
			envp->env[j] = NULL;
			return ;
		}
		i++;
	}
}
