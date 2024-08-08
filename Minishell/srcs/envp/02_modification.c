/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_modification.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:53:02 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/08 13:47:48 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Fonction pour +1 un int
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

// Fonction pour -1 un int
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