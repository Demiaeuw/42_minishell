/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_mini_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:41:27 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/13 13:49:06 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_env_entry(char *key, char *value, char ***env)
{
	int		i;
	char	**new_env;
	char	*new_entry;
	char	**old_env; // Temporaire pour garder la référence de l'ancien env

	i = 0;
	while ((*env)[i])
		i++;
	new_env = safe_malloc((i + 2) * sizeof(char *));
	if (!new_env)
	{
		printf("Memory allocation failed for new_env\n");
		return ;  
	}

	new_entry = safe_malloc(strlen(key) + strlen(value) + 2);
	if (!new_entry)
	{
		free(new_env);
		printf("Memory allocation failed for new_entry\n");
		return ;  
	}
	ft_strcpy(new_entry, key);
	ft_strcat(new_entry, "=");
	ft_strcat(new_entry, value);

	i = 0;
	while ((*env)[i])
	{
		new_env[i] = (*env)[i];
		i++;
	}
	new_env[i] = new_entry;
	new_env[i + 1] = NULL;
	
	old_env = *env;  // Sauvegarde de l'ancien env
	*env = new_env;  // Mise à jour du pointeur env

	free(old_env);  // Libération de l'ancien env
}


void	exe_export(char *input, char ***env)
{
	char	*key;
	char	*value;
	char	*equal_sign;

	if (!input || !env || !*env)
	{
		printf("Invalid input or env\n");
		return ;
	}

	input += 7; // Ignorer "export "
	equal_sign = strchr(input, '=');
	if (!equal_sign)
	{
		printf("Invalid input format, no '=' found\n");
		return ; 
	}

	key = safe_malloc(equal_sign - input + 1);
	if (!key)
	{
		printf("Memory allocation failed for key\n");
		return ;  
	}
	ft_strncpy(key, input, equal_sign - input);
	key[equal_sign - input] = '\0';

	value = equal_sign + 1;

	printf("Key: %s, Value: %s\n", key, value);

	if (get_env_value(key, *env) != NULL)
	{
		set_env_value(*env, key, value);
		printf("Updated existing key: %s\n", key);
	}
	else
	{
		add_env_entry(key, value, env);
		printf("Added new key-value pair: %s=%s\n", key, value);
	}

	free(key);
}

