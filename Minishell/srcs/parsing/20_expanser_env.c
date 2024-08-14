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

static char	*expand_variables_in_value(const char *value, char **env)
{
	size_t	len;
	char	*result;
	size_t	i;
	size_t	j;
	size_t	var_start;
	int		in_single_quotes;

	len = strlen(value);
	result = safe_malloc(len * 2 + 1);
	i = 0;
	j = 0;
	in_single_quotes = 0;
	while (i < len)
	{
		if (value[i] == '\'')
		{
			in_single_quotes = !in_single_quotes;
			result[j++] = value[i++];
		}
		else if (value[i] == '$' && !in_single_quotes)
		{
			i++;
			var_start = i;
			while (i < len && (ft_isalnum(value[i]) || value[i] == '_'))
				i++;
			char *var_name = strndup(&value[var_start], i - var_start);
			char *env_value = get_env_value(var_name, env);
			free(var_name);
			if (env_value)
			{
				size_t env_len = ft_strlen(env_value);
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

char *clean_string(const char* str) {
    int len = strlen(str);
    char* cleaned_str = (char*)malloc(len + 1);
    if (cleaned_str == NULL) {
        return NULL; // Gestion d'erreur si l'allocation échoue
    }
    
    int i, j = 0;
    int in_single_quote = 0;
    int in_double_quote = 0;

    for (i = 0; i < len; i++) {
        if (str[i] == '\'' && !in_double_quote) {
            in_single_quote = !in_single_quote;
        } else if (str[i] == '\"' && !in_single_quote) {
            in_double_quote = !in_double_quote;
        } else if (str[i] == '\'' && in_double_quote) {
            cleaned_str[j++] = str[i];
        } else if (str[i] == '\"' && in_single_quote) {
            cleaned_str[j++] = str[i];
        } else if (str[i] != '\'' && str[i] != '\"') {
            cleaned_str[j++] = str[i];
        }
    }

    cleaned_str[j] = '\0';
    return cleaned_str;
}

void	process_token_values(t_token *token, char **env)
{
	t_token *current;
	char	*expanded_value;

	current = token;
	if(token->is_builtin == true)
	{
		while (current != NULL)
		{
			expanded_value = expand_variables_in_value(current->value, env);
			free(current->value);
			if (!ft_strcmp(token->builtin_info, "echo"))
				expanded_value = clean_string(expanded_value);
			current->value = expanded_value;
			current = current->next;
		}
	}
}
