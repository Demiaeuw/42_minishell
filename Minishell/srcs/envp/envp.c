/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 19:48:45 by gaesteve          #+#    #+#             */
/*   Updated: 2024/08/07 16:03:59 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// FICHIER RESPONSABLE DE LA GESTION DES VARIABLES D ENVIRONNEMENT.

#include "envp.h"

/**
 * parcourt la liste chainee envp_list jusqu a
 * trouver une variable d env avec la
 * bonne cle(son nom).
 * des qu on trouve la correspondance, on retourne sa valeur associee a la cle.
 *
 * ca serait pour afficher le chemin de recherche des execs par exemple
*/
char	*envp_find(t_env *envp_list, char *key)
{
	t_node *node;

	node = list_peek_first_node(envp_list);
	while (node->content && ft_strcmp(((t_envp *)node->content)->key, key))
		node = node->next;
	if (node->content)
		return (((t_envp *)node->content)->value);
	return (NULL);
}

/**
 * Met a jour la valeur de la var d env
 * existante ou ca en creer une si y en a pas.
 * si y a correspondance, ca free l ancienne
 * valeur et assigne la nouvelle si y en
 * a une.
 * sinon ca fait comme envp_add juste en dessous :)
 * par exemple si on veut ajouter un nouveau repertoire au PATH
 * ou si on doit stocker des infos de configuration ou changer le repertoire
*/
void	envp_edit(t_env *envp_list, char *key, char *value)
{
	t_node *node;

	node = list_peek_first_node(envp_list);
	while (node->content && ft_strcmp(((t_envp *)node->content)->key, key))
		node = node->next;
	free(((t_envp *)node->content)->value);
	if (value)
		((t_envp *)node->content)->value = ft_strdup(value);
	else
		((t_envp *)node->content)->value = 0;
}

/**
 * ajoute une nouvelle var d env a la liste chainee ou ca met a jour celle qui
 * existe deja.
 * Si la cle existe ( on verifie ca avec envp exist) on apelle envp_edit.
 * sinon on free pour une nouvelle var d env,
 * on definit sa cle et sa valeur, puis
 * on l ajoute a la liste chainee.
*/
void	envp_add(t_env *envp_list, char *key, char *value)
{
	t_envp	*e_node;

	if (envp_exist(envp_list, key))
		return (envp_edit(envp_list, key, value));
	e_node = (t_envp *)ft_calloc(1, sizeof(t_envp));
	e_node->key = ft_strdup(key);
	if (value)
		e_node->value = ft_strdup(value);
	else
		e_node->value = 0;
	list_append(envp_list, new_node(e_node));
}

/**
 * on init la liste chainee avec nos var d env dedans a partir du tableau envp.
 * on parcourt le tableau, on extrait la cle et la valeur de chaque entree puis
 * on apelle envp_add pour y ajouter ou mettre
 * a jour la var d env correspondante.
 *
 * En gros au demarrage du programme on appelle cette fonction pour creer
 * la structure contenant les variables de l environnement.
*/
void	envp_init(t_env *env, char **envp)
{
	int		i;
	size_t	end_key;
	char	*key;
	char	*value;

	env->head = NULL;
	env->tail = NULL;
	env->size = 0;
	i = 0;
	while (envp[i])
	{
		end_key = 0;
		while (envp[i][end_key] && envp[i][end_key] != '=')
			end_key++;
		key = ft_substr(envp[i], 0, end_key);
		value = ft_strdup(ft_strchr(envp[i], '=') + 1);
		envp_add(env, key, value);
		free(key);
		free(value);
		i++;
	}
}

/**
 * Pour supprimer une var d env de la liste chainee selon sa cle.
 * ca va chercher la var d env selon la cle specifiee, si on trouve une
 * correspondance, on free sa valeur et sa cle, on la retire de la liste et on
 * free la memoire.
 * utile si on a une variable temporaire pour un truc specifique on peut la supp
 * quand on en a plus besoin
*/
void	envp_delete(t_env *envp_list, char *key)
{
	t_node *node;

	node = list_peek_first_node(envp_list);
	while (node->content && ft_strcmp(((t_envp *)node->content)->key, key))
		node = node->next;
	if (!node->content)
		return ;
	free(((t_envp *)node->content)->value);
	free(((t_envp *)node->content)->key);
	free(node->content);
	node->prev->next = node->next;
	node->next->prev = node->prev;
	free(node);
}
