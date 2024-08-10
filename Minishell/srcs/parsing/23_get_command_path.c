/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   23_get_command_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 23:46:07 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/10 23:47:45 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 *  Fonction pour concaténer deux chaînes avec un "/" entre elles
 */
char	*join_path(const char *path, const char *cmd)
{
	char	*full_path;
	size_t	len;

	len = strlen(path) + strlen(cmd) + 2;
	full_path = (char *)malloc(len);
	if (!full_path)
		return (NULL);
	strcpy(full_path, path);
	strcat(full_path, "/");
	strcat(full_path, cmd);
	return (full_path);
}

/**
 *  Fonction pour récupérer le chemin absolu d'une commande
 */
char	*get_command_path(const char *cmd)
{
	char	*path_env;
	char	**paths;
	char	*command_path;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (strdup(cmd)); // Si cmd est déjà un chemin absolu valide

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);

	paths = ft_split(path_env, ':'); // Fonction à implémenter pour split par ':'
	if (!paths)
		return (NULL);

	i = 0;
	while (paths[i])
	{
		command_path = join_path(paths[i], cmd);
		if (command_path && access(command_path, X_OK) == 0)
		{
			free(paths);
			return (command_path);
		}
		free(command_path);
		i++;
	}

	free(paths);
	return (NULL); // Commande non trouvée dans PATH
}