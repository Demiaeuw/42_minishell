/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10.parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:53:07 by acabarba          #+#    #+#             */
/*   Updated: 2024/07/19 18:42:25 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Main de gestion des arguments
 * 1/ split comme il faut
 * 2/ créer les tokens par type au fur et a meusure des arguments en liste chainé
 * 3/ free le tab de char
 * 4/ retourne la liste chainé de tokken
 */
char	**main_argument(int ac, char **av)
{
	char	**args;

	args = step01(ac, av);
	if (!args)
		return (NULL);
	// step 2
	// free args
	return (args);
}


/**
 *  Fonction pour split tous les arguments comme ils doivent etre split
 */ 
char	**step01(int ac, char **av)
{
	int		i;
	int		j;
	char	**args;

	if (ac < 2)
		return (NULL);
	args = (char **)safe_malloc(ac * sizeof(char *));
	i = 1;
	j = 0;
	while (i < ac)
	{
		args[j] = ft_strdup(av[i]);
		i++;
		j++;
	}
	args[j] = NULL;
	return (args);
}



/**
 * creation de tokken + ajout du type en fonction de ce qu'il y a ecrit et retourne la liste chainé
 */ 
void	*step02(char **array)
{
	// création du noeud
	// comparaison pour savoir quel type de token c'est
	// ajout du type de Token 
	// ajout de la value du token 
	// passe au suivant
}

void	token_compare(????)
{
	// compare le text a tout les token possible :
	
	// * TOKEN_COMMAND : Représente une commande (ex: "ls", "cd" etc...)
 	// * TOKEN_ARGUMENT : Représente un argument de commande (ex: "-l")
 	// * TOKEN_PIPE : Représente le caractère de pipe ('|')
 	// * TOKEN_REDIRECTION : Représente les redirections ('>', '<', '>>' , '<<')
 	// * TOKEN_STRING : Représente une chaîne de caractères entre guillemets 
 	// * TOKEN_VARIABLE : Représente une variable d'environnement (ex: "$PATH")
 	// * TOKEN_UNKNOWN : Représente un type de token inconnu ou non défini
}
