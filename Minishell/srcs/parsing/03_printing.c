/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_printing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:19:19 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/08 13:26:17 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Fonction pour obtenir le nom du type de token en tant que chaîne de caractères
 */
char	*get_token_type_name(t_token_type type)
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
		printf("Token_info : %s\n", token->builtin_info);
		printf("Token is_last_command : %d\n", token->is_last_command);
		printf("\n\n");
		token = token->next;
	}
}

void	signature(void)
{
	printf("\nMini_Shell 42 [version 10.0.22631.3958]\n");
	printf("by Yoan Onieva / Gauthier Esteve / Adrien Cabarbaye "
		"/ (and sometime Kevin Pourcel)\n");
	printf("(c) Gardiens de Phare [GDP]. Tous droits réservés.\n\n\n");
}
