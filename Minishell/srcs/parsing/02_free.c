/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 19:23:14 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/11 14:28:08 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_token_value(void *value)
{
	free(value);
}

/**
 * exemple d'appel de cette fonction : free_token(&token, free_token_value)
 */
void	free_token_list(t_token **lst, void (*del)(void*))
{
	t_token	*current;
	t_token	*next;

	if (!del || !lst || !*lst)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		del(current->value);
		if (current->builtin_info)
			free(current->builtin_info);
		free(current);
		current = next;
	}
	*lst = NULL;
}

/**
 * Fonction pour libérer un tableau de chaînes de caractères
 */
void	free_split_result(char **result)
{
	int	i;

	if (result == NULL)
		return ;
	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
}

/**
 * Fonction pour free un tableau de tableau 
 */
void	ft_free_tab(char **tab)
{
	int	i;

	if (!tab)
		return;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
