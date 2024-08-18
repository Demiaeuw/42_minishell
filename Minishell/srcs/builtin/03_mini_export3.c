/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_mini_export3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 20:07:10 by gaesteve          #+#    #+#             */
/*   Updated: 2024/08/18 20:18:27 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**allocate_and_copy_env(char **env, int size)
{
	char	**sorted_env;
	int		i;

	sorted_env = malloc(size * sizeof(char *));
	if (!sorted_env)
		return (NULL);
	i = 0;
	while (i < size)
	{
		sorted_env[i] = env[i];
		i++;
	}
	return (sorted_env);
}

void	print_env_var(char *env_var)
{
	char	*equal_sign;

	equal_sign = ft_strchr(env_var, '=');
	if (equal_sign == NULL)
		printf("declare -x %s\n", env_var);
	else if (equal_sign[1] == '\0')
		printf("declare -x %.*s=\"\"\n", (int)(equal_sign - env_var), env_var);
	else
		printf("declare -x %s\n", env_var);
}

void	print_sorted_env(char **env)
{
	int		i;
	int		size;
	char	**sorted_env;

	size = get_env_size(env);
	sorted_env = allocate_and_copy_env(env, size);
	if (!sorted_env)
		return ;
	qsort(sorted_env, size, sizeof(char *), compare_env_vars);
	i = 0;
	while (i < size)
	{
		print_env_var(sorted_env[i]);
		i++;
	}
	free(sorted_env);
}
