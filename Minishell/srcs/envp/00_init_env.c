/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:24:44 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/12 16:19:18 by gaesteve         ###   ########.fr       */
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

void	init_terminal(char **env)
{
	edit_shlvl(env);
}

char	**env_dup(char **env)
{
	int		var_env;
	char	**dup_env;
	int		i;

	var_env = 0;
	i = 0;

	while(env[var_env] != NULL)
		var_env++;
	dup_env = malloc((var_env + 1) * sizeof(char *));
	if (!dup_env)
		return (NULL);
	while (i < var_env)
	{
		dup_env[i] = ft_strdup(env[i]);
		i++;
	}
	dup_env[var_env] = NULL;
	return(dup_env);
}
