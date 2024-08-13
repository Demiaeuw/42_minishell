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

int exe_cd(char *input, t_envp *envp)
{
	char *old_pwd;
	char *new_pwd;
	char cwd[1024];
	char *path;

	if (strncmp(input, "cd", 2) != 0)
		return -1;
	path = input + 2;
	while (*path == ' ')
		path++;
	if (*path == '\0' || strcmp(path, "~") == 0)
		path = get_env_value("HOME", envp->env);
	old_pwd = getcwd(cwd, sizeof(cwd));
	if (!old_pwd)
	{
		perror("cd: error retrieving current directory");
		return 1;
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		return 1;
	}
	new_pwd = getcwd(cwd, sizeof(cwd));
	if (!new_pwd)
	{
		perror("cd: error retrieving new directory");
		return 1;
	}
	set_env_value(envp->env, "OLDPWD", old_pwd);
	set_env_value(envp->env, "PWD", new_pwd);
	return 0;
}
