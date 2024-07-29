/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:53:07 by acabarba          #+#    #+#             */
/*   Updated: 2024/07/29 12:13:53 by acabarba         ###   ########.fr       */
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
t_token	*main_argument(int ac, char **av)
{
	char	**args;
	t_token	*token_list;
	t_token	*simplified_list;

	args = step01(ac, av);
	if (!args)
		return (NULL);
	token_list = step02(args);
	free_split_result(args);
	simplified_list = simplify_list(token_list);
	free_token_list(&token_list, free_token_value);
	return (simplified_list);
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
	args[j] = (NULL);
	return (args);
}

/**
 * creation de tokken + ajout du type en fonction de ce qu'il y a ecrit et retourne la liste chainé 
 */ 
t_token	*step02(char **array)
{
	t_token		*token_list;
	t_token		*new_token;
	token_type	type;
	int			i;
	
	token_list = NULL;
	i = 0;
	while (array[i])
	{
		// Déterminer le type de token
		type = token_compare(array[i]);
		// Créer le nouveau token
		new_token = create_token(type, array[i]);
		// Ajouter le token à la liste chaînée
		add_token(&token_list, new_token);
		// Passer à l'élément suivant
		i++;
	}
	return (token_list);
}
