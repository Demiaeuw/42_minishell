/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_printing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:19:19 by acabarba          #+#    #+#             */
/*   Updated: 2024/07/29 15:52:15 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Fonction pour obtenir le nom du type de token en tant que chaîne de caractères
 */
char	*get_token_type_name(token_type type)
{
	if (type == TOKEN_COMMAND)
		return ("COMMAND");
	else if (type == TOKEN_ARGUMENT)
		return ("ARGUMENT");
	else if (type == TOKEN_PIPE)
		return ("PIPE");
	else if (type == TOKEN_REDIRECTION)
		return ("REDIRECTION");
	else if (type == TOKEN_VARIABLE)
		return ("VARIABLE");
	else
		return ("STRING");
}

/**
 * Fonction pour afficher les tokens
 */
void	print_tokens(t_token *token)
{
	while (token != NULL)
	{
		printf("TOKEN_TYPE : %s\n", get_token_type_name(token->type));
		printf("Token value : %s\n", token->value);
		printf("Token builtin : %d\n", token->is_builtin);
		printf("Token is_last_command : %d\n", token->is_last_command);
		token = token->next;
	}
}