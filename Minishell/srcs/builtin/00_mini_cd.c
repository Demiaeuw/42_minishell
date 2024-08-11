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

static void	update_env_pwd(t_envfinal *env, const char *new_pwd)
{
    t_envfinal *current;

    current = env;
    while (current)
    {
        if (!ft_strcmp(current->type, "PWD"))
        {
            free(current->content);
            current->content = strdup(new_pwd);
            break;
        }
        current = current->next;
    }
}

void	exe_cd(t_token *token, t_envfinal *env)
{
    char *path = token->value;
    char cwd[1024];

    if (!path || ft_strcmp(path, "~") == 0) // Si aucun chemin n'est fourni ou si "~" est utilisé
    {
        path = find_envcontent(env, "HOME");
        if (!path)
        {
            write(2, "cd: HOME not set\n", 17);
            return;
        }
    }

    if (chdir(path) == -1)
    {
        perror("cd");
        free(path); // Libère la mémoire allouée par find_envcontent
        return;
    }

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        update_env_pwd(env, cwd);
    }
    else
    {
        perror("getcwd");
    }

    free(path); // Libère la mémoire allouée par find_envcontent
}
