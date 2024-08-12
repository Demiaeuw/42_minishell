/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_mini_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 22:31:46 by yonieva           #+#    #+#             */
/*   Updated: 2024/08/12 22:31:46 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int exe_cd(char *input, char **env)
{
    char *old_pwd;
    char *new_pwd;
    char cwd[1024];
    char *path;

    // Vérifier si la commande est bien "cd" au début
    if (strncmp(input, "cd", 2) != 0)
        return -1; // Retourne une erreur si la commande n'est pas "cd"

    // Passer la commande "cd" et l'espace éventuel pour obtenir le chemin
    path = input + 2;
    while (*path == ' ') // Ignorer les espaces après "cd"
        path++;

    // Si aucun chemin n'est donné, utiliser la valeur de HOME
    if (*path == '\0' || strcmp(path, "~") == 0)
        path = get_env_value("HOME", env);

    // Récupérer l'ancien répertoire
    old_pwd = getcwd(cwd, sizeof(cwd));
    if (!old_pwd)
    {
        perror("cd: error retrieving current directory");
        return 1;
    }

    // Changer de répertoire
    if (chdir(path) != 0)
    {
        perror("cd");
        return 1;
    }

    // Récupérer le nouveau répertoire
    new_pwd = getcwd(cwd, sizeof(cwd));
    if (!new_pwd)
    {
        perror("cd: error retrieving new directory");
        return 1;
    }

    // Mettre à jour les variables d'environnement OLDPWD et PWD
    set_env_value(env, "OLDPWD", old_pwd);
    set_env_value(env, "PWD", new_pwd);

    return 0;
}
