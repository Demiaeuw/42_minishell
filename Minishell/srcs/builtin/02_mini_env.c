/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_mini_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:02:26 by gaesteve          #+#    #+#             */
/*   Updated: 2024/08/18 20:16:44 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	mini_env(t_envp *envp)
{
	int		i;
	char	*equal_sign;

	i = 0;
	while (envp->env[i])
	{
		equal_sign = ft_strchr(envp->env[i], '=');
		if (equal_sign && equal_sign[1] != '\0')
			printf("%s\n", envp->env[i]);
		i++;
	}
}
