/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_mini_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:55:21 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/13 23:27:01 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void exe_unset(t_envp *envp, char *args)
{
    char *var = args;

    // Skip the leading "unset " part if it's there
    if (strncmp(var, "unset ", 6) == 0)
        var += 6;

    if (*var)
    {
        printf("Unsetting variable: %s\n", var); // Debugging print
        unset_variable(envp, var);
    }
}

void unset_variable(t_envp *envp, const char *var)
{
    int i = 0;
    int j;
    int var_len = ft_strlen(var);

    printf("Looking for variable: %s\n", var); // Debugging print

    while (envp->env[i])
    {
        if (ft_strncmp(envp->env[i], var, var_len) == 0 && envp->env[i][var_len] == '=')
        {
            printf("Found and unsetting: %s\n", envp->env[i]); // Debugging print
            free(envp->env[i]);
            j = i;
            while (envp->env[j])
            {
                envp->env[j] = envp->env[j + 1];
                j++;
            }
            return;
        }
        i++;
    }
}
