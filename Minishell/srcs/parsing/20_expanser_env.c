/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_expanser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:39:20 by yonieva           #+#    #+#             */
/*   Updated: 2024/08/11 14:39:20 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expand_variables_in_value(const char *value, char **env)
{
	size_t	len;
	char	*result;
	size_t	i;
	size_t	j;
	int		in_single_quotes;

	len = strlen(value);
	result = safe_malloc(len * 2 + 1);  // Allocation de mémoire initiale
	i = 0;
	j = 0;
	in_single_quotes = 0;

	while (i < len)
	{
		if (value[i] == '\'')
		{
			in_single_quotes = !in_single_quotes; // Toggle entre guillemets simples
			result[j++] = value[i++];
		}
		else if (value[i] == '$' && !in_single_quotes)
		{
			i++; // Passer le '$'
			size_t var_start = i;
			// Trouver la fin du nom de la variable
			while (i < len && (ft_isalnum(value[i]) || value[i] == '_'))
				i++;
			char *var_name = strndup(&value[var_start], i - var_start);
			char *env_value = get_env_value(var_name, env);
			free(var_name);
			if (env_value)
			{
				size_t env_len = ft_strlen(env_value);
				// Réallocation de `result` si nécessaire
				result = realloc(result, j + env_len + (len - i) + 1);
				ft_memcpy(&result[j], env_value, env_len);
				j += env_len;
			}
		}
		else
			result[j++] = value[i++];
	}
	result[j] = '\0';
	return (result);
}


void	process_token_values(t_token *token, char **env)
{
	t_token *current;
	char	*expanded_value;

	current = token;
	while (current != NULL)
	{
		expanded_value = expand_variables_in_value(current->value, env);
		free(current->value); // Libérer l'ancienne valeur
		current->value = expanded_value; // Mettre à jour avec nouvelle valeur
		current = current->next;
	}
}
