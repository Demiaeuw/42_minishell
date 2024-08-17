/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_pathing_gestion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 23:46:07 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/18 00:53:46 by yonieva          ###   ########.fr       */
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

	len = ft_strlen(path) + ft_strlen(cmd) + 2;
	full_path = (char *)malloc(len);
	if (!full_path)
		return (NULL);
	ft_strcpy(full_path, path);
	ft_strcat(full_path, "/");
	ft_strcat(full_path, cmd);
	return (full_path);
}

/**
 *  Fonction pour récupérer le chemin absolu d'une commande
 */
static char	*try_access_command(char **paths, const char *cmd)
{
	char	*command_path;
	int		i;

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
	return (NULL);
}

char	*get_command_path(const char *cmd)
{
	char	*path_env;
	char	**paths;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	return (try_access_command(paths, cmd));
}
