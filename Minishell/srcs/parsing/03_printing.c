/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_printing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:19:19 by acabarba          #+#    #+#             */
/*   Updated: 2024/07/24 17:08:34 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Fonction pour obtenir le nom du type de token en tant que chaîne de caractères
 */
char	*get_token_type_name(token_type type)
{
	if (type == TOKEN_COMMAND)
		return "COMMAND";
	else if (type == TOKEN_ARGUMENT)
		return "ARGUMENT";
	else if (type == TOKEN_PIPE)
		return "PIPE";
	else if (type == TOKEN_REDIRECTION)
		return "REDIRECTION";
	else if (type == TOKEN_VARIABLE)
		return "VARIABLE";
	else
		return "STRING";
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
		token = token->next;
	}
}