/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_analyse1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:08:57 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/14 12:38:24 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Fonction de gestion des builtins
 * 1. Liste des builtins
 * 2. Vérification si c'est un buitin
 * 3. Ajout du Buitin_infos
 */
bool	is_builtin_command(char *com)
{
	return (!strcmp(com, "cd") || !strcmp(com, "echo") || !strcmp(com, "pwd")
		|| !strcmp(com, "env") || !strcmp(com, "export")
		|| !strcmp(com, "unset") || !strcmp(com, "exit"));
}

bool	check_builtin(char *value)
{
	char	*temp;
	int		i;
	int		len;
	bool	is_builtin;

	i = 0;
	len = 0;
	while (value[len] && value[len] != ' ')
		len++;
	temp = malloc(sizeof(char) * (len + 1));
	if (!temp)
		return (false);
	while (i < len)
	{
		temp[i] = value[i];
		i++;
	}
	temp[i] = '\0';
	is_builtin = is_builtin_command(temp);
	free(temp);
	return (is_builtin);
}

char	*get_builtin_info(char *value)
{
	char	*temp;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (value[len] && value[len] != ' ')
		len++;
	temp = malloc(sizeof(char) * (len + 1));
	if (!temp)
		return (NULL);
	while (i < len)
	{
		temp[i] = value[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}
