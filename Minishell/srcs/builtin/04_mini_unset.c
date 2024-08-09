/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_mini_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:14:09 by gaesteve          #+#    #+#             */
/*   Updated: 2024/08/09 15:43:53 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Unset : Supprime une/des variable(s) d envrionnement d une liste.

void	delete_env(t_envfinal **env, char *key)
{
	t_envfinal	*current;
	t_envfinal	*previous;

	current = *env;
	previous = NULL;
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
	free(current->type);
	free(current->content);
	free(current);
}

int	mini_unset(t_token *token, t_envfinal *env)
{
	char	*str;
	int		i = 0;
	int		j = 0;

	str = safe_malloc(sizeof(char) * ft_strlen(token->value));
	while (token->value[i] == ' ')
		i++;
	i += 5;
	while (token->value[i] == ' ')
		i++;
	while (token->value[i])
	{
		str[j] = token->value[i];
		i++;
		j++;
	}
	delete_env(&env, str);
	free(str);
	return (0);
}
