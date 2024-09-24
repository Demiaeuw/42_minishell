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

/**
 * Fonction built-in qui permet de naviger dans les repertoires.
 */
int	exe_cd(char *input, t_envp *envp)
{
	char	*old_pwd;
	char	*new_pwd;
	char	cwd[BUFFER_SIZE];
	char	*path;

	if (ft_strncmp(input, "cd", 2) != 0)
		return (-1);
	path = input + 2;
	while (*path == ' ')
		path++;
	if (*path == '\0' || ft_strcmp(path, "~") == 0)
		path = get_env_value("HOME", envp->env);
	old_pwd = getcwd(cwd, sizeof(cwd));
	if (!old_pwd)
		return (error_flag(), 1);
	if (chdir(path) != 0)
		return (ft_printf("cd: no such file or directory: %s\n", path), 1);
	new_pwd = getcwd(cwd, sizeof(cwd));
	if (!new_pwd)
		return (error_flag(), 1);
	set_env_value(envp->env, "OLDPWD", old_pwd);
	set_env_value(envp->env, "PWD", new_pwd);
	return (0);
}
