/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_envp_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:24:36 by gaesteve          #+#    #+#             */
/*   Updated: 2024/08/14 13:49:01 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}

char	*get_env_value(char *str, char **env)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(str);
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], str, len) == 0 && env[i][len] == '=')
			return (ft_strdup(env[i] + len + 1));
		i++;
	}
	return (NULL);
}

void	set_env_value(char **env, char *key, char *new_value)
{
	int		i;
	char	*temp;
	int		key_len;

	i = 0;
	if (!env || !key || !new_value)
		return ;
	key_len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
		{
			free(env[i]);
			temp = safe_malloc(strlen(key) + strlen(new_value) + 2);
			ft_strcpy(temp, key);
			ft_strcat(temp, "=");
			ft_strcat(temp, new_value);
			env[i] = temp;
			return ;
		}
		i++;
	}
	return ;
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

// void	free_t_envp(t_envp *envp)
// {
// 	int	i;

// 	if (envp == NULL)
// 		return ;
// 	if (envp->env)
// 	{
// 		i = 0;
// 		while (envp->env[i] != NULL)
// 		{
// 			free(envp->env[i]);
// 			i++;
// 		}
// 		free(envp->env);
// 	}
// 	free(envp);
// }
void	free_t_envp(t_envp *envp)
{
	int	i;

	if (envp == NULL)
		return ;
	if (envp->env)
	{
		i = 0;
		while (envp->env[i] != NULL)
		{
			printf("Freeing env[%d]: %p\n", i, envp->env[i]);
			free(envp->env[i]);
			i++;
		}
		printf("Freeing env: %p\n", envp->env);
		free(envp->env);
	}
	printf("Freeing envp: %p\n", envp);
	free(envp);
}
