/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_cleaning_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:38:46 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/08 15:18:11 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Ajoute un nouveau token avec la valeur combinée à la liste simplifiée.
 */
void	add_combined_token(t_token **simplst, char **combival, bool *firstcmd)
{
	t_token	*new_token;

	if (*combival)
	{
		new_token = create_token(TOKEN_COMMAND, *combival);
		add_token(simplst, new_token);
		free(*combival);
		*combival = NULL;
		*firstcmd = true;
	}
}

/**
 * Ajoute un token de type pipe à la liste simplifiée.
 */
void	add_pipe_token(t_token **simplified_list)
{
	t_token	*new_token;

	new_token = create_token(TOKEN_PIPE, "|");
	add_token(simplified_list, new_token);
}

/**
 * Combine la valeur actuelle avec la valeur précédente.
 */
void	combine_value(char **combival, char *current_value, bool *firstcmd)
{
	char	*temp;

	if (*firstcmd)
	{
		*combival = ft_strdup(current_value);
		*firstcmd = false;
	}
	else
	{
		temp = ft_strjoin(*combival, " ");
		free(*combival);
		*combival = ft_strjoin(temp, current_value);
		free(temp);
	}
}

/**
 * Simplification de la liste de tokens.
 */
t_token	*simplify_list(t_token *token)
{
	t_token	*simplst;
	t_token	*current;
	char	*combival;
	bool	firstcmd;

	simplst = NULL;
	current = token;
	combival = NULL;
	firstcmd = true;
	while (current)
	{
		if (current->type == TOKEN_COMMAND || current->type == TOKEN_ARGUMENT
			|| current->type == TOKEN_STRING || current->type == TOKEN_VARIABLE)
			combine_value(&combival, current->value, &firstcmd);
		else if (current->type == TOKEN_PIPE)
		{
			add_combined_token(&simplst, &combival, &firstcmd);
			add_pipe_token(&simplst);
		}
		current = current->next;
	}
	add_combined_token(&simplst, &combival, &firstcmd);
	return (simplst);
}
