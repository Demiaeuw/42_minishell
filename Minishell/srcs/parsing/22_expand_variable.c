/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   22_expand_variable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:34:34 by yonieva           #+#    #+#             */
/*   Updated: 2024/07/31 12:34:34 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/* ************************************************************************** */
/* Fonction auxiliaire pour étendre la chaîne avec realoc*/
char	*extend_result(char *result, size_t *result_size, size_t add_size)
{
	char	*new_result;
	size_t	new_size;

	new_size = *result_size + add_size;
	new_result = ft_realloc(result, *result_size, new_size);
	if (!new_result)
	{
		free(result);
		return (NULL);
	}
	*result_size = new_size;
	return (new_result);
}
/* ************************************************************************** */
/* Fonction pour retourner la valeur d'une variable d'env à la char*          */
char *append_var(char *res, const char *var, t_env *envp_list, size_t size)
{
	char *var_value;
	size_t var_len;

	var_value = envp_find(envp_list, var_name);
	var_len = 0;

	free((char*)var_name);

	if(var_value)
	{
		var_len = ft_strlen(var_value);
		if(*size - (res - res) < var_len)
		{
			res = extend_result(res, size, var_len);
			if(!res)
				return (NULL);
		}
		ft_strcat(res, var_value);
	}
	retrun (res);
}
/* ************************************************************************** */
/*Extrait le nom de la variable*/
char *process_var(const char *start, const char **end,
					char *res, size_t size,
					char **res_ptr, t_env *envp_list)
{
	char *var_name;

	var_name = ft_strndup(start, *end = start);
	if(!var_name)
	{
		free(res);
		return (NULL);
	}
	res = append_var(res, var_name, envp_list, size);
	if (!res)
		return (NULL);
	*res_ptr = res + ft_strlen(res);
	return (res);
}
/* ************************************************************************** */
/* Fonction principale pour l'expansion des variables d'environnement */
char *expend_variable(const char *input, t_env *envp_list)
{
	size_t input_len;
	size_t res_size;
	char *res;
	const char *start;
	char *res_ptr;
	const char *end;

	input_len = ft_strlen(input);
	res_size = input_len + 1;
	res = safe_malloc(res_size);
	start = input;
	res_ptr = res;
	while (*start)
	{
		if(*start == '$')
			start++;
			end = start;
			while(*end && (ft_isalnum(*end) || *end == '_'))
				end++;
			res = process_var(start, &end, res, &res_size, &res_ptr, envp_list);
			if (!res)
				return (NULL);
			start = end;
		else
			*res_ptr++ = *start++;
	}
	*res_ptr = '\0';
	return (res);
}
