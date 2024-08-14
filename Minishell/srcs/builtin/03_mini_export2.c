/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_mini_export2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 00:45:04 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/14 18:32:20 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
// Sets a new env variable or updates an existing one
void	set_env_var(t_envp *envp, const char *var, const char *value)
{
	int		var_len;
	char	*new_entry;

	var_len = ft_strlen(var);
	new_entry = create_env_entry(var, value);
	if (!new_entry)
		return ;
	update_env(envp, var, var_len, new_entry);
}

// Updates the env with the new entry or adds it if it doesn't exist
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
	add_env_variable(envp, new_entry);
}

// Processes an export token and adds or updates the corresponding env variable
void	process_export_token(t_envp *envp, char *token)
{
	char	*equal_sign;
	char	*var;
	char	*value;

	equal_sign = ft_strchr(token, '=');
	if (!equal_sign)
		return ;
	var = ft_strndup(token, equal_sign - token);
	value = equal_sign + 1;
	if (var && *var)
		set_env_var(envp, var, value);
	free(var);
}

// Executes the export command to add or update env variables
void	exe_export(t_envp *envp, char *args)
{
	char	*token;
	char	*saveptr;

	if (!args)
		return ;
	if (ft_strncmp(args, "export ", 7) == 0)
		args += 7;
	token = ft_strtok(args, " ", &saveptr);
	while (token != NULL)
	{
		process_export_token(envp, token);
		token = ft_strtok(NULL, " ", &saveptr);
	}
}
