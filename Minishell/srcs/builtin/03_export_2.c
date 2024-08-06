/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_export_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:33:19 by gaesteve          #+#    #+#             */
/*   Updated: 2024/08/06 15:21:24 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * creer un tableau de str avec les keys des variables d env dedans.
 *
 * On alloue de la memoire pour que ce soit cleqn, et ensuite on parcourt la
 * liste des var d env en copiant chaque key dans le tableau
 *
 * cur_node est un pointeur sur le noeud actuel et nous permet de naviguer
 * dans tous les noeuds de la liste.
*/
char	**extract_keys(t_env *envp_list)
{
	int		i;
	t_node	*cur_node;
	char	**key_arr;

	i = 0;
	key_arr = (char **)ft_calloc(list_size(envp_list) + 1, sizeof(char *));
	cur_node = list_peek_first_node(envp_list);
	while (cur_node->next)
	{
		key_arr[i] = ((t_envp *)cur_node->content)->key;
		cur_node = cur_node->next;
		i++;
	}
	key_arr[i] = 0;
	return(key_arr);
}

/**
 * ici on trie le tableau de keys par ordre alphabetique.
 *
 * on utilise le tri a bulle pour trier et on compare les key et on les echange
 * si elles ne sont pas dans le bon ordre
*/
void	sort_keys(char **key_arr)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (key_arr[i])
	{
		j = i + 1;
		while (key_arr[i])
		{
			if (ft_strcmp(key_arr[i], key_arr[j]) > 0)
			{
				temp = key_arr[i];
				key_arr[i] = key_arr[j];
				key_arr[j] = temp;
			}
			j++;
		}
		i++;
	}
}

/**
 * pour afficher les var d env.
 *
 * on creer et trie le tableau de keys avec nos fonctions juste au dessus, et
 * on parcourt keys_tab pour afficher toutes les var d env.
*/
void	print_export(t_env *envp_list)
{
	char	**keys_tab;
	char	*key;
	char	*value;
	int		i;

	i = 0;
	keys_tab = extract_keys(envp_list);
	sort_keys(keys_tab);
	while (key_arr[i])
	{
		key = keys_tab[i];
		value = envp_find(envp_list, key);
		if (value)
			printf("", key, value);
		else
			printf("", key);
		i++;
	}
	free(keys_tab);

}
