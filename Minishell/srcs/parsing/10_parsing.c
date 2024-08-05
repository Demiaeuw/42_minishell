/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:53:07 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/06 01:10:27 by acabarba         ###   ########.fr       */
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
t_token	*main_parse(char *str)
{
	char	**args;
	t_token	*token_list;
	t_token	*simplified_list;

	args = step01(str);
	if (!args)
		return (NULL);
	token_list = step02(args);
	free_split_result(args);
	simplified_list = simplify_list(token_list);
	free_token_list(&token_list, free_token_value);
	last_command(simplified_list);
	add_builtin(simplified_list);
	return (simplified_list);
}

/**
 *  Fonction pour split tous les arguments comme ils doivent etre split
 */
char	**step01(char *str)
{
	int		i;
	int		j;
	int		k;
	char	quote_char;
	char	**args;

	if (!str)
		return (NULL);

	// Allocation mémoire pour le pire cas (chaque caractère est un mot)
	args = (char **)safe_malloc((ft_strlen(str) / 2 + 2) * sizeof(char *));
	i = 0;
	k = 0;
	quote_char = 0;

	while (str[i])
	{
		// Passer les espaces initiaux
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i] == '\0')
			break;

		// Allocation mémoire pour le prochain argument
		args[k] = (char *)safe_malloc((ft_strlen(str) - i + 1) * sizeof(char));
		j = 0;

		// Gérer les guillemets simples et doubles
		if (str[i] == '"' || str[i] == '\'')
		{
			quote_char = str[i++];
			while (str[i] && str[i] != quote_char)
				args[k][j++] = str[i++];
			if (str[i] == quote_char)
				i++; // Passer le guillemet fermant
			quote_char = 0; // Réinitialiser la variable de guillemet
		}
		else
		{
			// Copier le mot jusqu'au prochain espace ou la fin de la chaîne
			while (str[i] && !ft_isspace(str[i]) && str[i] != '"' && str[i] != '\'')
				args[k][j++] = str[i++];
		}
		args[k][j] = '\0'; // Terminer l'argument actuel
		k++;
	}
	args[k] = NULL; // Terminer le tableau de tableaux

	return (args);
}

/**
 * creation de tokken + ajout du type en fonction de ce 
 * qu'il y a ecrit et retourne la liste chainé
 */
t_token	*step02(char **array)
{
	t_token		*token_list;
	t_token		*new_token;
	t_token_type	type;
	int			i;

	token_list = NULL;
	i = 0;
	while (array[i])
	{
		type = token_compare(array[i]);
		new_token = create_token(type, array[i]);
		add_token(&token_list, new_token);
		i++;
	}
	return (token_list);
}
