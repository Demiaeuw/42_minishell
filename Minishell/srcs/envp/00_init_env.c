/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:24:44 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/14 13:48:57 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	edit_shlvl(char **env)
{
	char	*new_value;
	char	*old_value;

	while (*env)
	{
		if (ft_strncmp(*env, "SHLVL=", 6) == 0)
		{
			old_value = ft_itoa(ft_atoi(*env + 6) + 1);
			if (old_value == NULL)
				return ;
			new_value = ft_strjoin("SHLVL=", old_value);
			free(old_value);
			if (new_value == NULL)
				return ;
			free(*env);
			*env = new_value;
			return ;
		} 
		env++;
	}
}

void	init_terminal(t_envp *envp)
{
	edit_shlvl(envp->env);
}

int	count_env_vars(char **env)
{
	int	count;

	count = 0;
	while (env[count] != NULL)
		count++;
	return (count);
}

char	**duplicate_env(char **env, int var_env)
{
	char	**dup_env;
	int		i;

	dup_env = malloc((var_env + 1) * sizeof(char *));
	if (!dup_env)
		return (NULL);
	i = 0;
	while (i < var_env)
	{
		dup_env[i] = ft_strdup(env[i]);
		if (!dup_env[i])
		{
			while (i > 0)
				free(dup_env[--i]);
			free(dup_env);
			return (NULL);
		}
		i++;
	}
	dup_env[var_env] = NULL;
	return (dup_env);
}

t_envp	env_dup(char **env)
{
	t_envp	dup_envp;
	int		var_env;

	var_env = count_env_vars(env);
	dup_envp.env = duplicate_env(env, var_env);
	return (dup_envp);
}
