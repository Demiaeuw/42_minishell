/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_token_comp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:43:33 by acabarba          #+#    #+#             */
/*   Updated: 2024/07/29 15:45:30 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

token_type	token_compare(char *arg)
{
	// compare le texte à tous les tokens possibles :
	
	// * TOKEN_COMMAND : Représente une commande (ex: "ls", "cd" etc...)
	if (ft_strcmp(arg, "cd") == 0 || ft_strcmp(arg, "ls") == 0
		|| ft_strcmp(arg, "echo") == 0 || ft_strcmp(arg, "export") == 0
		|| ft_strcmp(arg, "unset") == 0 || ft_strcmp(arg, "env") == 0 
		|| ft_strcmp(arg, "exit") == 0 || ft_strcmp(arg, "pwd") == 0
		|| ft_strcmp(arg, "cat") == 0 || ft_strcmp(arg, "grep") == 0
		|| ft_strcmp(arg, "mkdir") == 0  || ft_strcmp(arg, "rm") == 0)
		return (TOKEN_COMMAND);
	// * TOKEN_ARGUMENT : Représente un argument de commande (ex: "-l")
	else if (arg[0] == '-' && ft_strlen(arg) > 1)
		return (TOKEN_ARGUMENT);
	// * TOKEN_PIPE : Représente le caractère de pipe ('|')
	else if (ft_strcmp(arg, "|") == 0)
		return (TOKEN_PIPE);
	// * TOKEN_REDIRECTION : Représente les redirections ('>', '<', '>>' , '<<')
	else if (ft_strcmp(arg, ">") == 0 || ft_strcmp(arg, ">>") == 0
		|| ft_strcmp(arg, "<") == 0 || ft_strcmp(arg, "<<") == 0)
		return (TOKEN_REDIRECTION);
	// * TOKEN_VARIABLE : Représente une variable d'environnement (ex: "$PATH")
	else if (ft_strcmp(arg, "$HOME") == 0 || ft_strcmp(arg, "$PATH") == 0
		|| ft_strcmp(arg, "$PWD") == 0)
		return (TOKEN_VARIABLE);
	// * TOKEN_STRING : Représente une chaîne de caractères entre guillemets ou une string simple
	else
		return (TOKEN_STRING);
}

void	last_command(t_token *token)
{
	t_token	*current = token;

	while (current)
	{
		if (current->type == TOKEN_COMMAND && (current->next == NULL))
			current->is_last_command = true;
		else
			current->is_last_command = false;

		current = current->next;
	}
}

