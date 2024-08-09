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

// int	exe_cd(char *str, t_envfinal *envp_list)
// {
// 	char	old_pwd[PATH_MAX];
// 	char	new_pwd[PATH_MAX];
// 	char	*dest;

// /*Si aucun str , on recupere juste la variable HOME*/
// /*puisque quand on fait 'cd' sans argument, on reste au meme endroit.*/
// 	if (str == NULL)
// 		dest = find_envcontent(envp_list, "HOME");
// /*Sinon, utilise l argument comme répertoire de destination.*/
// 	else
// 		dest = str;
// 	old_pwd[0] = '\0';
// 	getcwd(old_pwd, PATH_MAX);
// /*Tente de changer de répertoire vers dest avec 'chdir' (ft incluse en C)*/
// 	if (chdir(dest) == -1)
// 		return (1);
// 	if (!getcwd(new_pwd, PATH_MAX))
// 		return(1);
// 	/* Si old_pwd est vide mais que PWD est définie,*/
// 	/*copie la valeur de PWD dans old_pwd.*/
// 	if (!ft_strlen(old_pwd) && find_envcontent(envp_list, "PWD"))//////////////////////////////////////////////////////////////////////////////////////
// 		ft_strcpy(old_pwd, find_envcontent(envp_list, "PWD"));
// 	/*maj des variables OLD_PWD et PWD*/
// 	modif_env(envp_list, "OLDPWD", old_pwd);
// 	modif_env(envp_list, "PWD", old_pwd);
// 	return (0);
// }
// /* ************************************************************************** */

void	exe_cd(char *path, t_envfinal *env)
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
}
