/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relativ_to_absolute.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:46:46 by yonieva           #+#    #+#             */
/*   Updated: 2024/07/17 14:46:46 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char    *get_absolute_path(const char *relative_path)
{
	/*Recuperer avec getcwd le chemin courant*/
	char	courant_path[PATH_MAX];
	int		len;
	char	*absolute_path;

	if (getcwd(courant_path, sizeof(courant_path)) == NULL)
		main_error(ft_error, 2);
	/*Allouer de la mémoire pour le chemin absolu*/
	len = ft_strlen(courant_path) + ft_strlen(relative_path) + 2;
	absolute_path = safe_malloc(len);
	/*'2' pour le séparateur '/' et le caractère nul */

	/*Construire le chemin absolu*/
	ft_strcpy(absolute_path, courant_path);
	ft_strcat(absolute_path, "/");
	ft_strcat(absolute_path, relative_path);

	return (absolute_path);
}
