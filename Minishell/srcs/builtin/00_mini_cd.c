/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_mini_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 13:24:23 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/11 13:24:23 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "../../include/minishell.h"

static char	*get_env_value(t_envfinal *env, char *var)
{
	t_envfinal	*current = env;

	while (current)
	{
		if (strcmp(current->type, var) == 0)
			return (current->content);
		current = current->next;
	}
	return (NULL);
}

static void	update_env(t_envfinal *env, char *var, char *value)
{
	t_envfinal	*current = env;

	while (current)
	{
		if (strcmp(current->type, var) == 0)
		{
			free(current->content);
			current->content = strdup(value);
			return;
		}
		current = current->next;
	}
}

static char *get_target_path(t_token *token, t_envfinal *env)
{
	char	*path;
	char	*home;
	char	*oldpwd;

	if (!token->next || !token->next->value) // cd sans argument
	{
		home = get_env_value(env, "HOME");
		if (!home)
		{
			fprintf(stderr, "cd: HOME not set\n");
			return (NULL);
		}
		path = strdup(home);
	}
	else if (strcmp(token->next->value, "-") == 0) // cd -
	{
		oldpwd = get_env_value(env, "OLDPWD");
		if (!oldpwd)
		{
			fprintf(stderr, "cd: OLDPWD not set\n");
			return (NULL);
		}
		path = strdup(oldpwd);
		printf("%s\n", path); // Affiche le répertoire précédent
	}
	else
	{
		if (token->next->value[0] == '/')
			path = strdup(token->next->value); // Chemin absolu
		else
		{
			char cwd[1024];
			getcwd(cwd, sizeof(cwd));
			path = malloc(strlen(cwd) + strlen(token->next->value) + 2);
			sprintf(path, "%s/%s", cwd, token->next->value); // Chemin relatif
		}
	}
	return (path);
}

void	exe_cd(t_token *token, t_envfinal *env)
{
	char	*path;
	char	cwd[1024];

	// Récupère le chemin cible
	path = get_target_path(token, env);
	if (!path)
		return;

	// Récupère le répertoire courant avant de changer
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("getcwd failed");
		free(path);
		return;
	}

	// Change le répertoire
	if (chdir(path) != 0)
	{
		perror("cd failed");
		free(path);
		return;
	}

	// Met à jour les variables d'environnement OLDPWD et PWD
	update_env(env, "OLDPWD", cwd);
	if (getcwd(cwd, sizeof(cwd)))
		update_env(env, "PWD", cwd);

	free(path);
}
