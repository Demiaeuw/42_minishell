/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_export_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:33:06 by gaesteve          #+#    #+#             */
/*   Updated: 2024/07/30 17:18:12 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../envp/envp.h"

/**
 * Cherche la premiere occurence du char c dans une string et return son index.
 * sinon return -1 pour signaler qu on a rien trouve.
*/
int	ft_findchr_i(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return(i);
		i++;
	}
	return(-1);
}
/**
 * separe un mot en cle et valeur et verifie si la cle est valide.
 *
 * si on trouve '=' on extrait la cle de word.
 * par exemple : "PATH=/usr/bin", *key sera "PATH".
 * si on trouve pas '=' la totalite de word sera la cle.
 * par exemple : si word est "PATH" et qu y a pas de =, *key sera PATH.
 * on passe plein de verifs et si tout est bon on retourne 0 pour dire que tout
 * s est bien passe.
 *
 * autre exemple:
 * si word est "USER=root", *key sera USER et la valeur sera root.
 *
 * en gros, on separe ce qu il y a avant et apres le = en cle et valeur.
 * s y a pas d egal, on considere que tout est la cle.
 *
 * Ca permet de gerer les situations ou une var d env est definie sans valeur et
 * les cas ou une cle et une valeur sont fournies.
*/
int	check_word_sep(char *word, char **key, char **value, int *error_flag)
{
	int	equal_i;

	equal_i = ft_findchr_i(word, '=');
	if (equal_i == 0)
	{
		*error_flag = EXIT_FAILURE;
		gestion_erreur_bt("export", word, INVALID_ARG);
		return(1);
	}
	if (equal_i != -1)
		*key = ft_substr(word, 0, equal_i);
	else
		*key = word;
	if (!is_proper_env(*key))
	{
		*error_flag = EXIT_FAILURE;
		gestin_erreur_bt("export", word, INVALID_ARG);
		if (equal_i != -1)
			free(*key);
		return(1);
	}
	if (equal_i != -1)
		*value = ft_substr(word, equal_i + 1, ft_strlen(word) - equal_i - 1);
	return (0);
}
