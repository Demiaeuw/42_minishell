/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_modification.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:53:02 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/10 21:56:33 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Fonction pour +1 un int
 * Arguments :
 * 1. liste chainé de l'environement
 * 2. la nom de la variable a modifié (SHLVL=)
 */
void	increment_int(t_envfinal *env, char *str)
{
	t_envfinal	*current;
	int			temp;
	char		*new_content;

	current = env;
	while (current && ft_strcmp(current->type, str) != 0)
		current = current->next;
	if (current)
	{
		temp = ft_atoi(current->content);
		temp++;
		new_content = ft_itoa(temp);
		if (new_content)
		{
			free(current->content);
			current->content = new_content;
		}
	}
	return ;
}

/**
 * Fonction pour -1 un int
 * Arguments :
 * 1. liste chainé de l'environement
 * 2. la nom de la variable a modifié (SHLVL=)
 */
void	decrement_int(t_envfinal *env, char *str)
{
	t_envfinal	*current;
	int			temp;
	char		*new_content;

	current = env;
	while (current && ft_strcmp(current->type, str) != 0)
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

/**
 * Fonction pour modifier un char dans l'environement
 * Arguments :
 * 1. liste chainé de l'environement
 * 2. la nom de la variable a modifié (SHLVL=)
 * 3. le nouveau contenue de cette variable (=1)
 */
void	modif_env(t_envfinal *env, char *type_env, char *newcont)
{
	t_envfinal	*current;

	current = env;
	while (current && ft_strcmp(current->type, type_env))
		current = current->next;
	if (current)
	{
		free(current->content);
		current->content = safe_malloc(sizeof(char) * (ft_strlen(newcont) + 1));
		ft_strcpy(current->content, newcont);
	}
	return ;
}

/**
 * Fonction pour recuperer un content dans l'environement
 * Arguments :
 * 1. liste chainé de l'environement
 * 2. la nom de la variable a chercher (SHLVL=)
 * Sortie :
 * char * du contenue trouvé qui a été malloc
 */
char	*find_envcontent(t_envfinal *env, char *type_env)
{
	char		*result;
	t_envfinal	*current;

	current = env;
	while (current && ft_strcmp(current->type, type_env))
		current = current->next;
	result = safe_malloc(sizeof(char) * (ft_strlen(current->content) + 1));
	ft_strcpy(result, current->content);
	return (result);
}
