/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_mini_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:55:21 by acabarba          #+#    #+#             */
/*   Updated: 2024/09/20 18:21:17 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	shift_env_vars(char **env, int start)
{
	int	j;

	j = start;
	while (env[j])
	{
		env[j] = env[j + 1];
		j++;
	}
	env[j] = NULL;
}

void	unset_variable(t_envp *envp, const char *var)
{
	int	i;
	int	var_len;

	if (ft_strcmp(var, "_") == 0)
		return ;
	i = 0;
	var_len = ft_strlen(var);
	while (envp->env[i])
	{
		if (ft_strncmp(envp->env[i], var, var_len) == 0
			&& envp->env[i][var_len] == '=')
		{
			free(envp->env[i]);
			shift_env_vars(envp->env, i);
			break ;
		}
		i++;
	}
}

/**
 * Fonction qui permet de supprimer un variable d'env
 */
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
