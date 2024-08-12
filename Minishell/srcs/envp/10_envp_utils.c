/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_envp_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/08/12 17:40:04 by gaesteve         ###   ########.fr       */
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

void    set_env_value(char **env, char *key, char *new_value)
{
    int     i;
    char    *temp;
    int     key_len;

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

char	*get_env_value(char *str, char **env)
{
	int		i;
	size_t 	len;

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
