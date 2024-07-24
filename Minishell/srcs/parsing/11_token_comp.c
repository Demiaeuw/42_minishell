/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_token_comp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:43:33 by acabarba          #+#    #+#             */
/*   Updated: 2024/07/24 14:05:43 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

token_type	token_compare(char *arg)
{
	// compare le text a tout les token possible :
	
// * TOKEN_COMMAND : Représente une commande (ex: "ls", "cd" etc...)
	if (ft_strcmp(arg, "cd") == 0 || ft_strcmp(arg, "ls") == 0
		|| ft_strcmp(arg, "echo") == 0 || ft_strcmp(arg, "export") == 0
		|| ft_strcmp(arg, "unset") == 0 || ft_strcmp(arg, "env") == 0 
		|| ft_strcmp(arg, "exit") == 0 || ft_strcmp(arg, "pwd") == 0
		|| ft_strcmp(arg, "cat") == 0 || ft_strcmp(arg, "grep") == 0
		|| ft_strcmp(arg, "mkdir") == 0  || ft_strcmp(arg, "rm") == 0)
		return (TOKEN_COMMAND);
// * TOKEN_ARGUMENT : Représente un argument de commande (ex: "-l")
	else if (ft_strcmp(arg, "-l") == 0 || ft_strcmp(arg, "-a") == 0
		|| ft_strcmp(arg, "-n") == 0 || ft_strcmp(arg, "-p") == 0
		|| ft_strcmp(arg, "-i") == 0 || ft_strcmp(arg, "-v") == 0
		|| ft_strcmp(arg, "-r") == 0 || ft_strcmp(arg, "-f") == 0)
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
