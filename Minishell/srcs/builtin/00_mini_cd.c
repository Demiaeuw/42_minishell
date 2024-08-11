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

#include "../../include/minishell.h"

// Cette fonction récupère la valeur d'une variable d'environnement donnée
char *get_env_value2(const char *var, t_envfinal *env)
{
    t_envfinal *current = env;

    while (current)
    {
        if (strcmp(current->type, var) == 0)
            return (current->content);
        current = current->next;
    }
    return (NULL);
}

// Cette fonction met à jour la valeur d'une variable d'environnement
void update_env(t_envfinal *env, char *var, char *value)
{
    t_envfinal *current = env;

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

// Cette fonction détermine le chemin cible en fonction de la commande cd
char *get_target_path2(t_token *token, t_envfinal *env)
{
    char *path;
    char *home;
    char *oldpwd;

    if (!token->next || !token->next->value) // cd sans argument
    {
        home = get_env_value2("HOME", env);
        if (!home)
        {
            fprintf(stderr, "cd: HOME not set\n");
            return (NULL);
        }
        path = strdup(home);
    }
    else if (strcmp(token->next->value, "-") == 0) // cd -
    {
        oldpwd = get_env_value2("OLDPWD", env);
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

// Cette fonction exécute la commande cd
void exe_cd(t_token *token, t_envfinal *env)
{
    char *path;
    char cwd[1024];

    // Récupère le chemin cible
    path = get_target_path2(token, env);
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





// static void		print_error(char **args)
// {
// 	ft_putstr_fd("cd: ", 2);
// 	if (args[2])
// 		ft_putstr_fd("string not in pwd: ", 2);
// 	else
// 	{
// 		ft_putstr_fd(strerror(errno), 2);
// 		ft_putstr_fd(": ", 2);
// 	}
// 	ft_putendl_fd(args[1], 2);
// }

// static char	*get_env_path(t_envfinal *env, const char *var)
// {
// 	while (env)
// 	{
// 		if (ft_strcmp(env->type, var) == 0)
// 		{
// 			return (ft_strdup(env->content));
// 		}
// 		env = env->next;
// 	}
// 	return (NULL);
// }


// static int	update_oldpwd(t_envfinal *env)
// {
// 	char	cwd[PATH_MAX];
// 	t_envfinal *current;

// 	if (getcwd(cwd, PATH_MAX) == NULL)
// 		return (1);

// 	current = env;
// 	while (current)
// 	{
// 		if (strcmp(current->type, "OLDPWD") == 0)
// 		{
// 			free(current->content);  // Libère l'ancienne valeur de OLDPWD
// 			current->content = strdup(cwd);
// 			if (!current->content)
// 				return (1);
// 			return (0);
// 		}
// 		current = current->next;
// 	}

// 	// Si OLDPWD n'existe pas encore, l'ajouter
// 	t_envfinal *new_node = malloc(sizeof(t_envfinal));
// 	if (!new_node)
// 		return (1);
// 	new_node->type = strdup("OLDPWD");
// 	new_node->content = strdup(cwd);
// 	new_node->next = env->next;
// 	env->next = new_node;

// 	return (0);
// }


// static int	go_to_path(int option, t_envfinal *env)
// {
// 	int		ret;
// 	char	*env_path = NULL;

// 	if (option == 0)
// 	{
// 		update_oldpwd(env);
// 		env_path = get_env_path(env, "HOME");
// 		if (!env_path)
// 		{
// 			printf("minishell : cd: HOME not set");
// 			return (1);
// 		}
// 	}
// 	else if (option == 1)
// 	{
// 		env_path = get_env_path(env, "OLDPWD");
// 		if (!env_path)
// 		{
// 			printf("minishell : cd: OLDPWD not set");
// 			return (1);
// 		}
// 		update_oldpwd(env);
// 	}

// 	ret = chdir(env_path);
// 	return (ret);
// }


// static int	ft_cd(char **args, t_envfinal *env)
// {
// 	int	cd_ret;
// 	int		len;

// 	len = ft_tablen(args);
// 	if (len == 1)
// 		return (go_to_path(0, env)); // Aller à HOME si aucun argument

// 	if (ft_strcmp(args[1], "-") == 0)
// 		cd_ret = go_to_path(1, env); // Aller à OLDPWD si '-' est passé en argument
// 	else
// 	{
// 		update_oldpwd(env); // Met à jour OLDPWD avant de changer de répertoire
// 		cd_ret = chdir(args[1]); // Changer de répertoire vers le chemin spécifié
// 		if (cd_ret < 0)
// 			cd_ret *= -1;
// 		if (cd_ret != 0)
// 			print_error(args); // Afficher une erreur si chdir échoue
// 	}
// 	return (cd_ret);
// }


// int		transform_cd(t_envfinal *env, t_token *token)
// {
// 	char **args;
// 	args = ft_split(token->value, ' ');

// 	ft_cd(args, env);
// 	ft_free_tab(args);
// 	return (0);
// }