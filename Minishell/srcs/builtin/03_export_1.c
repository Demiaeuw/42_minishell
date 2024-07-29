/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_export_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:33:06 by gaesteve          #+#    #+#             */
/*   Updated: 2024/07/29 16:55:55 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../envp/envp.h"

int	ft_findchr_i(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return(i);
		i++;
	}
	return(-1);
}

int	is_proper_env(char *env_name)
{
	int	full_len;
	int	env_len;

	full_len = ft_strlen(env_name);
	env_len = get_env_len(env_name);
	if (full_len == env_len)
		return (1);
	else
		return (0);
}

int	check_word_sep(char *word, char **key, char **value, int *error_f)
{
	int	equal_i;

	equal_i = ft_findchr_i(word, '=');
	if (equal_i == 0)
	{
		//finir cette fonction
	}
}
