/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_mini_export1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:41:27 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/14 12:32:55 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*create_new_entry(const char *var, const char *value)
{
	int		var_len;
	int		value_len;
	char	*new_entry;

	var_len = strlen(var);
	value_len = strlen(value);
	new_entry = (char *)malloc(var_len + value_len + 2);
	if (!new_entry)
		return (NULL);
	strcpy(new_entry, var);
	new_entry[var_len] = '=';
	strcpy(new_entry + var_len + 1, value);
	return (new_entry);
}

void	update_env(t_envp *envp, const char *var, int var_len, char *new_entry)
{
	int	i;

	i = 0;
	while (envp->env[i])
	{
		if (ft_strncmp(envp->env[i], var, var_len) == 0
			&& envp->env[i][var_len] == '=')
		{
			free(envp->env[i]);
			envp->env[i] = new_entry;
			return ;
		}
		i++;
	}
	add_new_env_variable(envp, new_entry);
}

void	add_new_env_variable(t_envp *envp, char *new_entry)
{
	int		i;
	char	**new_env;

	i = 0;
	while (envp->env[i])
		i++;
	new_env = realloc(envp->env, (i + 2) * sizeof(char *));
	if (!new_env)
	{
		free(new_entry);
		return ;
	}
	envp->env = new_env;
	envp->env[i] = new_entry;
	envp->env[i + 1] = NULL;
}

void	add_or_update_env(t_envp *envp, const char *var, const char *value)
{
	int		var_len;
	char	*new_entry;

	var_len = strlen(var);
	new_entry = create_new_entry(var, value);
	if (!new_entry)
		return ;
	update_env(envp, var, var_len, new_entry);
}
