/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_init2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:37:43 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/08 15:15:43 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Fonction pour afficher la liste chaînée des variables d'environnement
 * Argument : 
 * 1. liste chainé de l'environement
 */ 
void	print_env_list(t_envfinal *env_list)
{
	while (env_list)
	{
		printf("%s=%s\n", env_list->type, env_list->content);
		env_list = env_list->next;
	}
}


/**
 * Fonction pour +1 un int
 * Argument : 
 * 1. liste chainé de l'environement
 */
void	increment_shlvl(t_envfinal *env)
{
	t_envfinal	*current;
	int			temp;
	char		*new_content;

	current = env;
	while (current && ft_strcmp(current->type, "SHLVL") != 0)
		current = current->next;
	if (current)
	{
		temp = ft_atoi(current->content);
		temp++;
		new_content = ft_itoa(temp);
		if (new_content)
		{
			free(current->content);
			current->content = new_content; // free content ici peut etre
		}
	}
	return ;
}

/**
 * Fonction pour -1 un int
 * Argument : 
 * 1. liste chainé de l'environement
 */
void	decrement_shlvl(t_envfinal *env)
{
	t_envfinal	*current;
	int			temp;
	char		*new_content;

	current = env;
	while (current && ft_strcmp(current->type, "SHLVL") != 0)
		current = current->next;
	if (current)
	{
		temp = ft_atoi(current->content);
		temp--;
		new_content = ft_itoa(temp);
		if (new_content)
		{
			free(current->content);
			current->content = new_content;
		}
	}
	return ;
}
