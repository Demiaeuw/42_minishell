/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_mini_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:37:29 by yonieva           #+#    #+#             */
/*   Updated: 2024/07/30 12:37:29 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	string_to_int(const char *str, int *result)
{
	int	value;
	int	sign;

	value = 0;
	sign = 1;
	while (*str == ' ')
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
	{
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		value = value * 10 + (*str - '0');
		str++;
	}
	if (*str != '\0')
		return (0);
	*result = value * sign;
	return (1);
}

void	exe_exit(char *str, char **env, t_token *token)
{
	int	exit_code;
	int	conversion_success;

	exit_code = 0;
	while (*str == ' ')
		str++;
	if (*str == '\0')
	{
		decrement_shlvl(env);
		free_token_list(token);
		return ;
	}
	conversion_success = string_to_int(str, &exit_code);
	if (!conversion_success || exit_code < 0 || exit_code > 255)
		exit_code = 1;
	decrement_shlvl(env);
	free_token_list(token);
	free_array(env);
	exit(exit_code);
}
