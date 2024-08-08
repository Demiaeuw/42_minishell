// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   03_export_1.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/07/29 14:33:06 by gaesteve          #+#    #+#             */
// /*   Updated: 2024/08/07 18:44:27 by acabarba         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../include/minishell.h"

// /**
//  * BUT DE LA FONCTION : avec cette commande on peut ajouter ou modifier des var
//  * de l env dans la liste des var d env du shell.
//  *
//  * par exemple si on veut ajouter une nouvelle variable :
//  * export PATH=/usr/local/bin
//  * separe PATH et /usr/local/bin grace au =,
//  * check si PATH est valide,
//  * ajoute PATH a la liste de var d env avec la valeur /usr/local/bin.
//  * si on fait ensuite PATH=/usr/bin ca va modifier sa valeur avec la nouvelle
//  * qu on vient de lui donner.
//  * et y a encore d autres utilisations mais je vais pas faire un commentaire de
//  * 800 LIGNES MERDE
//  * quel enfeeeeer, premier degreeeeeeees
//  */

// /**
//  * Cherche la premiere occurence du char c dans une string et return son index.
//  * sinon return -1 pour signaler qu on a rien trouve.
//  */
// int	ft_findchr_i(char *str, char c)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == c)
// 			return(i);
// 		i++;
// 	}
// 	return(-1);
// }
// /**
//  * separe word en key et value avec le sep '=' et check si key est valide.
//  *
//  * par exemple : "PATH=/usr/bin", *key sera "PATH".
//  * en gros, on separe ce qu il y a avant et apres le = en cle et valeur.
//  * si y a pas d egal, on considere que tout est la cle.
//  *
//  * Ca permet de gerer les situations ou une var d env est definie sans valeur et
//  * les cas ou une cle et une valeur sont fournies.
//  */
// int	check_word_sep(char *word, char **key, char **value, int *error_flag)
// {
// 	int	equal_i;

// 	equal_i = ft_findchr_i(word, '=');
// 	if (equal_i == 0)
// 	{
// 		*error_flag = EXIT_FAILURE;
// 		gestion_erreur_bt("export", word, INVALID_ARG);
// 		return(1);
// 	}
// 	if (equal_i != -1)
// 		*key = ft_substr(word, 0, equal_i);
// 	else
// 		*key = word;
// 	if (!is_proper_env(*key))
// 	{
// 		*error_flag = EXIT_FAILURE;
// 		gestion_erreur_bt("export", word, INVALID_ARG);
// 		if (equal_i != -1)
// 			free(*key);
// 		return(1);
// 	}
// 	if (equal_i != -1)
// 		*value = ft_substr(word, equal_i + 1, ft_strlen(word) - equal_i - 1);
// 	return (0);
// }

// /**
//  * sert a ajouter ou modifier des variables d environnement.
//  *
//  * on parcourt les arg, on check si ils sont ok et on les ajoute a envp_list.
//  *
//  * on utilise continue pour ne pas utiliser envp_add et un free si checkwordsep
//  * detecte une erreur, ca nous permet d eviter des operations inutiles ou des
//  * free incorrect
//  */
// int	mini_export(char **str, t_env *envp_list)
// {
// 	int		i;
// 	int		error_flag;
// 	char	*word;
// 	char	*key;
// 	char	*value;

// 	error_flag = EXIT_SUCCESS;
// 	i = 1;
// 	if (check_word_count(str) == 1)
// 		print_export(envp_list);
// 	while (str[i])
// 	{
// 		key = NULL;
// 		value = NULL;
// 		word = str[i];
// 		i++;
// 		if (check_word_sep(word, &key, &value, &error_flag))
// 			continue ;
// 		envp_add(envp_list, key, value);
// 		if (word != key)
// 			free(key);
// 		if (value)
// 			free(value);
// 	}
// 	return (error_flag);
// }