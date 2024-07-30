/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_mini_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:13:51 by yonieva           #+#    #+#             */
/*   Updated: 2024/07/30 11:13:51 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exe_pwd(char *str, t_list *envp_list)
{
	char temp[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL) 
	{
    	printf("\033[33m\n🚨Error !🚨\n\n'getcwd' fonction issue\n\n\033[0m");
        return 1;
    }
	printf("%s\n", temp);
	return (0);
}