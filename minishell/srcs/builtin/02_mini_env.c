/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_mini_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:02:26 by gaesteve          #+#    #+#             */
/*   Updated: 2024/09/20 18:18:44 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Fonction qui permet d'afficher l'environement du minishell (en fonction du 
 * SHLVL. ils n'ont pas tous le même).
 */
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
