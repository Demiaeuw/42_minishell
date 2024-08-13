/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:24:44 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/13 22:26:41 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	edit_shlvl(char **env)
{
	char	*tmp;

	while (*env)
	{
		if (ft_strncmp(*env, "SHLVL=", 6) == 0)
		{
			tmp = ft_strjoin(ft_strdup("SHLVL="), ft_itoa(ft_atoi(*env + 6)
						+ 1));
			free(*env);
			*env = tmp;
			break ;
		}
		env++;
	}
}

void	init_terminal(t_envp *envp)
{
	edit_shlvl(envp->env);
}

t_envp	env_dup(char **env)
{
	t_envp	dup_envp;
	int		var_env;
	int		i;

	var_env = 0;
	i = 0;
	while (env[var_env] != NULL)
		var_env++;
	dup_envp.env = malloc((var_env + 1) * sizeof(char *));
	if (!dup_envp.env)
	{
		dup_envp.env = NULL;
		return (dup_envp);
	}
	while (i < var_env)
	{
		dup_envp.env[i] = ft_strdup(env[i]);
		if (!dup_envp.env[i])
		{
			while (i > 0)
				free(dup_envp.env[--i]);
			free(dup_envp.env);
			dup_envp.env = NULL;
			return (dup_envp);
		}
		i++;
	}
	dup_envp.env[var_env] = NULL;
	return (dup_envp);
}
