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

#include "../include/minishell.h"

char    *get_absolute_path(const char *relative_path)
{
    /*Recuperer avec getcwd le chemin courant*/
    char courant_path[PATH_MAX];
    int len;
    if (getcwd(courant_path, sizeof(courant_path)) == NULL)
    {
        printf("\033[33m🚨Erreur fonction 'getcwd'🚨\n");
        ft_error(6);
    }
    /*Allouer de la mémoire pour le chemin absolu*/
    len = strlen(courant_path) + strlen(relative_path) + 2;
    char *absolute_path = safe_malloc(len);
    /*'2' pour le séparateur '/' et le caractère nul */

    /*Construire le chemin absolu*/
    strcpy(absolute_path, courant_path);
    strcat(absolute_path, "/");
    strcat(absolute_path, relative_path);

    return absolute_path;
}