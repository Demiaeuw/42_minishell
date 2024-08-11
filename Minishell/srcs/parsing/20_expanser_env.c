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

// Fonction pour obtenir la valeur d'une variable d'environnement
char	*get_env_value(const char *name, t_envfinal *env) 
{
    while (env != NULL) 
	{
        if (strcmp(env->type, name) == 0) 
            return env->content;
        env = env->next;
    }
    return NULL;
}

// Fonction pour expander les variables d'environnement dans un token
char *expand_variables_in_value(const char *value, t_envfinal *env) 
{
    size_t len = strlen(value);
    char *result = malloc(len * 2 + 1);
    if (!result) return NULL;

    size_t i = 0, j = 0;
    while (i < len) 
	{
        if (value[i] == '$' && (i == 0 || isspace(value[i - 1]))) 
		{
            i++;  // Passer le '$'
            size_t var_start = i;

            // Trouver la fin du nom de la variable
            while (i < len && (isalnum(value[i]) || value[i] == '_')) 
                i++;
            char *var_name = strndup(&value[var_start], i - var_start);
            char *env_value = get_env_value(var_name, env);
            free(var_name);

            if (env_value) 
			{
                size_t env_len = strlen(env_value);
                // Réallocation de `result` si nécessaire
                result = realloc(result, j + env_len + (len - i) + 1);
                memcpy(&result[j], env_value, env_len);
                j += env_len;
            }
        } 
		else 
        	result[j++] = value[i++];
    }

    result[j] = '\0';
    return result;
}

void	process_token_values(t_token *token, t_envfinal *env) 
{
    t_token *current = token;

    while (current != NULL) 
	{
        char *expanded_value = expand_variables_in_value(current->value, env);
        free(current->value);  // Libérer l'ancienne valeur
        current->value = expanded_value;  // Mettre à jour avec la nouvelle valeur
        current = current->next;
    }
}
