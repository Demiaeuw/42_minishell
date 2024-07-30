/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_cleaning_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:38:46 by acabarba          #+#    #+#             */
/*   Updated: 2024/07/30 11:14:42 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Simplification de la liste
 * On passe du détail complet à une structure plus simple
 */
t_token	*simplify_list(t_token *token)
{
	t_token	*simplified_list;
	t_token	*current;
	t_token	*new_token;
	char	*combined_value;
	size_t	combined_length;
	bool	first_command;

	simplified_list = NULL;
	current = token;
	new_token = NULL;
	combined_value = NULL;
	combined_length = 0;
	first_command = true;
	while (current)
	{
		if (current->type == TOKEN_COMMAND || current->type == TOKEN_ARGUMENT
			|| current->type == TOKEN_STRING || current->type == TOKEN_VARIABLE)
		{
			combined_length += strlen(current->value) + 1;
			combined_value = (char *)realloc(combined_value, combined_length);
			if (first_command)
			{
				strcpy(combined_value, current->value);
				first_command = false;
			}
			else
			{
				strcat(combined_value, " ");
				strcat(combined_value, current->value);
			}
		}
		else if (current->type == TOKEN_PIPE)
		{
			new_token = create_token(TOKEN_COMMAND, combined_value);
			add_token(&simplified_list, new_token);
			free(combined_value);
			combined_value = NULL;
			combined_length = 0;
			first_command = true;

			new_token = create_token(TOKEN_PIPE, "|");
			add_token(&simplified_list, new_token);
		}
		current = current->next;
	}
	if (combined_value)
	{
		new_token = create_token(TOKEN_COMMAND, combined_value);
		add_token(&simplified_list, new_token);
		free(combined_value);
	}
	return (simplified_list);
}
