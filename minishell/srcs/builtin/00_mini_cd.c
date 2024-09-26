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
	char	*home_path = NULL;  // To keep track of HOME path if dynamically allocated

	if (ft_strncmp(input, "cd", 2) != 0)
		return (-1);
	path = input + 2;
	while (*path == ' ')
		path++;
	if (*path == '\0' || ft_strcmp(path, "~") == 0)
	{
		home_path = get_env_value("HOME", envp->env);
		if (!home_path)
			return (printf("cd: HOME not set\n"), 1);
		path = home_path;  // Assign dynamically allocated HOME path
	}
	old_pwd = getcwd(cwd, sizeof(cwd));
	if (!old_pwd)
		return (error_flag(), 1);
	if (chdir(path) != 0)
	{
		if (home_path)
			free(home_path);  // Free dynamically allocated HOME path
		return (printf("cd: no such file or directory: %s\n", path), 1);
	}
	new_pwd = getcwd(cwd, sizeof(cwd));
	if (!new_pwd)
	{
		if (home_path)
			free(home_path);  // Free dynamically allocated HOME path
		return (error_flag(), 1);
	}
	set_env_value(envp->env, "OLDPWD", old_pwd);
	set_env_value(envp->env, "PWD", new_pwd);

	if (home_path)
		free(home_path);  // Free dynamically allocated HOME path after use
	return (0);
}

