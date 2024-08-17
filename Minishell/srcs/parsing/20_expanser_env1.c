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

char	*extract_var_name_env(const char *value, size_t *i)
{
	size_t	start;
	char	*var_name;

	start = *i;
	while (ft_isalnum(value[*i]) || value[*i] == '_')
		(*i)++;
	var_name = ft_strndup(&value[start], *i - start);
	return (var_name);
}

void	append_env_value_env(char **result, size_t *j, const char *env_value)
{
	size_t	env_len;
	char	*new_result;

	env_len = ft_strlen(env_value);
	new_result = realloc(*result, *j + env_len + 1);
	if (!new_result)
		return ;
	ft_memcpy(&new_result[*j], env_value, env_len);
	*j += env_len;
	*result = new_result;
}

void	start_exp(const char *va, char **r, size_t *i, size_t *j, char **env)
{
	char	*var_name;
	char	*env_value;

	var_name = extract_var_name_env(va, i);
	env_value = get_env_value(var_name, env);
	free(var_name);
	if (env_value)
		append_env_value_env(r, j, env_value);
}

char	*expand_variables_in_value(const char *value, char **env)
{
	size_t	i;
	size_t	j;
	int		in_single_quotes;
	size_t	len;
	char	*result;

	i = 0;
	j = 0;
	in_single_quotes = 0;
	len = ft_strlen(value);
	result = safe_malloc(len * 2 + 1);
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
			start_exp(value, &result, &i, &j, env);
		}
		else
			result[j++] = value[i++];
	}
	result[j] = '\0';
	return (result);
}

char	*clean_string(const char *str)
{
	int		i;
	int		j;
	int		in_single_quote;
	int		in_double_quote;
	int		len;
	char	*cleaned_str;

	len = ft_strlen(str);
	cleaned_str = (char *)malloc(len + 1);
	if (!cleaned_str)
		return (NULL);
	i = 0;
	j = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (i < len)
	{
		if (str[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (str[i] == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if ((str[i] == '\'' && in_double_quote) || 
		         (str[i] == '\"' && in_single_quote) || 
		         (str[i] != '\'' && str[i] != '\"'))
			cleaned_str[j++] = str[i];
		i++;
	}
	cleaned_str[j] = '\0';
	return (cleaned_str);
}