/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_cleaning_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:38:46 by acabarba          #+#    #+#             */
/*   Updated: 2024/07/29 12:12:13 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

#include "../../include/minishell.h"

/**
 * Simplification de la liste
 * On passe du détail complet à une structure plus simple
 */
t_token	*simplify_list(t_token *token)
{
	t_token	*new_list;
	t_token	*current;
	char	*combined_value;
	size_t	total_length;

	if (!token)
		return (NULL);
	total_length = 0;
	current = token;
	while (current)
	{
		if (current->type != TOKEN_PIPE)
			total_length += ft_strlen(current->value) + 1;
		current = current->next;
	}
	combined_value = (char *)safe_malloc(total_length * sizeof(char));
	combined_value[0] = '\0';
	current = token;
	while (current)
	{
		if (current->type != TOKEN_PIPE)
		{
			ft_strcat(combined_value, current->value);
			ft_strcat(combined_value, " ");
		}
		current = current->next;
	}
	new_list = create_token(TOKEN_COMMAND, combined_value);
	free(combined_value);
	current = token;
	while (current)
	{
		if (current->type == TOKEN_PIPE)
			add_token(&new_list, create_token(TOKEN_PIPE, current->value));
		current = current->next;
	}
	return (new_list);
}
