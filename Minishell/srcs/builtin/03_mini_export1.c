/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_mini_export1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:41:27 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/17 23:49:38 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
// Creates a new env entry in the format "var=value"
char	*create_env_entry(const char *var, const char *value)
{
	int		var_len;
	int		value_len;
	char	*new_entry;

	var_len = ft_strlen(var);
	value_len = ft_strlen(value);
	new_entry = (char *)malloc(var_len + value_len + 2);
	if (!new_entry)
		return (NULL);
	ft_strcpy(new_entry, var);
	new_entry[var_len] = '=';
	ft_strcpy(new_entry + var_len + 1, value);
	return (new_entry);
}

// Returns the size of the env (number of entries)
int	get_env_size(char **env)
{
	int	size;

	size = 0;
	while (env[size])
		size++;
	return (size);
}

// Allocates a new env array of size new_size and copies old_env into it
char	**allocate_env_array(char **old_env, int old_size, int new_size)
{
	char	**new_env;
	int		i;

	new_env = malloc(new_size * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < old_size)
	{
		new_env[i] = old_env[i];
		i++;
	}
	return (new_env);
}

// Adds a new env variable to envp
void	add_env_variable(t_envp *envp, char *new_entry)
{
	int		old_size;
	char	**new_env;

	old_size = get_env_size(envp->env);
	new_env = allocate_env_array(envp->env, old_size, old_size + 2);
	if (!new_env)
	{
		free(new_entry);
		return ;
	}
	free(envp->env);
	envp->env = new_env;
	envp->env[old_size] = new_entry;
	envp->env[old_size + 1] = NULL;
}
