/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_analyse2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:33:42 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/12 13:40:19 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Fonctions qui permettent la transformation des chaine de char
 * pour les passer au bon format :
 * 1. fermer les quotes si ce n'a pas été fait.
 * 2. retirer les espaces qui ne devrai pas etre present.
 */
char	*close_quotes_if_needed(char *str)
{
	int len = strlen(str);
	int i;
	bool single_quote_open = false;
	bool double_quote_open = false;

	// Parcourir la chaîne pour vérifier les guillemets ouverts
	while (i < len)
	{
		if (str[i] == '\'')
			single_quote_open = !single_quote_open;
		else if (str[i] == '"')
			double_quote_open = !double_quote_open;
		i++;
	}

	// Si un guillemet est resté ouvert, on ferme en ajoutant à la fin
	char *new_str = malloc(len + 2); // +1 pour le guillemet manquant +1 pour le '\0'
	if (!new_str)
		return NULL;

	strcpy(new_str, str);

	if (single_quote_open)
		new_str[len++] = '\'';
	else if (double_quote_open)
		new_str[len++] = '"';

	new_str[len] = '\0';
	return new_str;
}


char	*clean_whitespace(char *str)
{
    int i = 0, j = 0;
    int len = strlen(str);
    char *cleaned_str = malloc(len + 1); // Allocation mémoire pour la chaîne nettoyée

    if (!cleaned_str)
        return NULL;

    // Ignorer les espaces au début
    while (str[i] == ' ')
        i++;

    while (str[i])
    {
        // Copier le caractère actuel
        cleaned_str[j++] = str[i];

        // Ignorer les espaces multiples
        if (str[i] == ' ' && str[i + 1] == ' ')
        {
            while (str[i] == ' ')
                i++;
            continue;
        }

        i++;
    }

    // Supprimer les espaces en fin de chaîne
    if (j > 0 && cleaned_str[j - 1] == ' ')
        j--;

    cleaned_str[j] = '\0';
    return cleaned_str;
}

