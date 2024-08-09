/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_mini_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:33:06 by gaesteve          #+#    #+#             */
/*   Updated: 2024/08/09 15:42:08 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * BUT DE LA FONCTION : avec cette commande on peut ajouter ou modifier des var
 * de l env dans la liste des var d env du shell.
 *
 * par exemple si on veut ajouter une nouvelle variable :
 * export PATH=/usr/local/bin
 * separe PATH et /usr/local/bin grace au =,
 * check si PATH est valide,
 * ajoute PATH a la liste de var d env avec la valeur /usr/local/bin.
 * si on fait ensuite PATH=/usr/bin ca va modifier sa valeur avec la nouvelle
 * qu on vient de lui donner.
 */

/**
 * Création d'une char * qui prend le type qu'on veut modifier
 * doit etre free
 */
static char	*env_type(char *str)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && !ft_isspace(str[i]))
		i++;
	while (ft_isspace(str[i]))
		i++;
	while (str[i + j] && str[i + j] != '=')
		j++;
	result = (char *)safe_malloc(sizeof(char) * (j + 1));
	ft_strncpy(result, &str[i], j);
	result[j] = '\0';
	return (result);
}

/**
 * Création d'une char * qui prend le content qu'on veut modifier
 * doit etre free
 */
static char	*env_content(char *str)
{
	char	*result;
	int		i;

	i = 0;
	while (str[i] && !ft_isspace(str[i]))
		i++;
	while (ft_isspace(str[i]))
		i++;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		i++;
	result = ft_strdup(&str[i]);
	return (result);
}

/**
 * Main export
 */
void	exe_export(t_envfinal *env, t_token *token)
{
	t_envfinal	*current;
	char		*type;
	char		*content;

	current = env;
	type = env_type(token->value);
	content = env_content(token->value);
	while (current && ft_strcmp(current->type, type) != 0)
		current = current->next;
	if (current)
	{
		free(current->content);
		current->content = ft_strdup(content);
	}
	else
	{
		current = create_env_node(type, content);
		add_env_node(&env, current);
	}
	free(type);
	free(content);
}
