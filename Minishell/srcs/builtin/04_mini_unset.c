// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   04_mini_unset.c                                    :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/07/30 16:14:09 by gaesteve          #+#    #+#             */
// /*   Updated: 2024/08/07 14:33:02 by acabarba         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../include/minishell.h"

// Utilisation : pour supprimer des variables d envrionnement d une liste.

/*
// Supprime une variable de l env de la liste chainee.
// on traverse la liste jusqu a ce qu on trouve la cle
void	delete_env(t_envfinal **env, char *key)
{
	t_envfinal *current = *env;
	t_envfinal *previous = NULL;

	while (current != NULL && strcmp(current->type, key) != 0)
	{
		previous = current;
		current = current->next;
	}
	if (current == NULL)
		return ;
	if (previous == NULL)
		*env = current->next;
	else
		previous->next = current->next;
	//ici on pourra free ce qu il faut je pense
}

int	mini_unset(char **cmd_str, t_envfinal **env)
{
	bool	error_flag = false;
	int		i = 1;

	while (cmd_str[i])
	{
		if (!is_proper_env(cmd_str[i]))
		{
			error_flag = true;
			printf("unset: '%s' : invalid argument\n", cmd_str[i]);
		}
		else
		{
			delete_env(env, cmd_str[i]);
		}
		i++;
	}
	return (error_flag);
}
*/