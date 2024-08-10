/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_mini_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:18:12 by yonieva           #+#    #+#             */
/*   Updated: 2024/07/22 10:18:12 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "../../include/minishell.h"


int 	exe_cd(char *str, t_envfinal *env)
{
    char old_pwd[PATH_MAX];
    char new_pwd[PATH_MAX];
    char *dest;

    // Si aucun chemin n'est fourni, utiliser la valeur de HOME
    if (str == NULL || strlen(str) == 0)
    {
        dest = find_envcontent(env, "HOME");
        if (!dest)
        {
            fprintf(stderr, "cd: HOME not set\n");
            return 1;
        }
    }
    else
    {
        dest = str;
    }

    // Récupérer le répertoire courant actuel
    if (!getcwd(old_pwd, sizeof(old_pwd)))
    {
        perror("getcwd");
        return 1;
    }

    // Changer de répertoire
    if (chdir(dest) == -1)
    {
        perror("cd");
        return 1;
    }

    // Récupérer le nouveau répertoire courant
    if (!getcwd(new_pwd, sizeof(new_pwd)))
    {
        perror("getcwd");
        return 1;
    }

    // Mettre à jour OLDPWD et PWD dans l'environnement
    if (find_envcontent(env, "PWD") && strlen(old_pwd) == 0)
    {
        char *pwd = find_envcontent(env, "PWD");
        if (pwd)
        {
            strncpy(old_pwd, pwd, sizeof(old_pwd) - 1);
            old_pwd[sizeof(old_pwd) - 1] = '\0'; // Assurer la terminaison de la chaîne
        }
    }

    modif_env(env, "OLDPWD", old_pwd);
    modif_env(env, "PWD", new_pwd);

    return 0;
}

/*void	exe_cd(char *path, t_envfinal *env)
{
	char	*old_pwd;
	char	*new_pwd;
	int		ret;

	// Récupère l'ancienne valeur de PWD (chemin actuel)
	old_pwd = find_envcontent(env, "PWD");

	// Si le chemin est relatif, le convertir en chemin absolu
	if (is_relativ_path(path))
		clean_path(path);

	// Tentative de changer de répertoire
	ret = chdir(path);
	if (ret == -1)
	{
		perror("cd");
		free(old_pwd);
		return ;
	}

	// Récupère le nouveau chemin après changement de répertoire
	new_pwd = safe_malloc(PATH_MAX);
	if (getcwd(new_pwd, PATH_MAX) == NULL)
	{
		perror("getcwd");
		free(old_pwd);
		free(new_pwd);
		return ;
	}

	// Met à jour les variables d'environnement PWD et OLDPWD
	modif_env(env, "OLDPWD", old_pwd);
	modif_env(env, "PWD", new_pwd);

	// Libère la mémoire utilisée
	free(old_pwd);
	free(new_pwd);
}*/
