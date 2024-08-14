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


static void ft_strshift_left(char *str, int start)
{
	int i;

	i = start;
	while (str[i] != '\0')
	{
		str[i] = str[i + 1];
		i++;
	}
}

char *ft_remove_quotes(char *str)
{
    int i;
    int in_double_quotes;
    int in_single_quotes;

    if (!str)
        return NULL;
    i = 0;
    in_double_quotes = 0;
    in_single_quotes = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '"' && !in_single_quotes)
        {
            in_double_quotes = !in_double_quotes;
            ft_strshift_left(str, i);
        }
        else if (str[i] == '\'' && !in_double_quotes)
        {
            in_single_quotes = !in_single_quotes;
            ft_strshift_left(str, i);
        }
        else
            i++;
    }
    return (str);
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
			expanded_value = ft_remove_quotes(expanded_value);
			current->value = expanded_value;
			current = current->next;
		}
	}
}
