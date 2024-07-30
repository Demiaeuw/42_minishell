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

/* exe_cd*/
/* la fonction exe_cd retourne 0 si le changement de repertoire a reussi
sinon elle retourne 1*/
/*Gerer sortie du programme + free si retourne 1, pas le messagge d erreur*/
/* ************************************************************************** */
static  int	home(void)
{
	if (!envp_find(envp_list, "HOME"))
	{
		printf("\033[33m\n🚨No value for 'HOME'🚨\n[0m");
		return (-1);
	}
	return (0);
}
/* ************************************************************************** */
int	exe_cd(char *str, t_list *envp_list)
{
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];
	char	*dest;
	if (str == NULL && home() == -1)
		return(1);
/*Si aucun str , on recupere juste la variable HOME*/
/*puisque quand on fait 'cd' sans argument, on reste au meme endroit.*/
	if (str == NULL)
		dest = envp_find(envp_list, "HOME");
/*Sinon, utilise l argument comme répertoire de destination.*/
	else
		dest = str;
	old_pwd[0] = '\0';
	getcwd(old_pwd, PATH_MAX);
/*Tente de changer de répertoire vers dest avec 'chdir' (ft incluse en C)*/
	if (chdir(dest) == -1)
	{
		printf("🚨Error ! 'chdir' fail !🚨\n");
		return (1);
	}
	if (!getcwd(new_pwd, PATH_MAX))
	{
		printf("\033[33m\n🚨Error !🚨\n\n'getcwd' fonction issue\n\n\033[0m")
		return(1);
	}
	/* Si old_pwd est vide mais que PWD est définie,*/ 
	/*copie la valeur de PWD dans old_pwd.*/
	if (!ft_strlen(old_pwd) && get_env("PWD"))
		ft_strlcpy(old_pwd, get_env("PWD"));
	/*maj des variables OLD_PWD et PWD*/
	if	(!envp_edit(envp_list, OLDPWD, old_pwd)) || (!envp_edit(envp_list, PWD, new_pwd))
	{
		printf("🚨Error ! Maj environement fail !🚨\n");
		return (1); 
	}
	return (0);
}
/* ************************************************************************** */