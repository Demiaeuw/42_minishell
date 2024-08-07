/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_mini_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:37:29 by yonieva           #+#    #+#             */
/*   Updated: 2024/07/30 12:37:29 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void    exe_exit(char *str, t_env *envp_list, t_shell_level *shell)
{
	(void)str;
	(void)envp_list;
	(void)shell;
	printf("ici on quitte le programe au propre\n\n");
}
// void    exe_exit(char *str, t_env *envp_list, t_shell_level *shell)
// {
// 	char space_pos[1024];
// 	int	exit_code = 0;
// 	int is_number = 1;

// 	while (*str == ' ')
// 		str++;
// 	if (*str  == '\0')
// 	{
// 		if (shell->level > 0)
// 		{
// 			shell->level--;
// 			return; // Retourne sans fermer le shell si le niveau est > 0
// 		}
// 		else
// 			//FREEEEEEEEEEE
// 			exit(0);// Pas d'argument, terminer avec code 0
// 	}
// 	char *space_pos = ft_strchr(str,' ');
// 	if (space_pos != NULL)
// 		space_pos++;
// 	while(*space_pos == ' ')
// 		space_pos++;
// 	if (*space_pos != '\0')
// 	{
// 		exit_code = 0;
// 		while (*space_pos >= '0' && *space_pos <= '9')
// 		{
// 			exit_code = exit_code * 10 + (*space_pos = '0');
// 			space_pos++;
// 		}
// 		if (exit_code < 0 || exit_code > 255)
// 			exit_code = 1;
// 	}
// 	if (shell->level > 0)
// 	{
// 		shell->level--;
// 		return;
// 	}
// 	//FREEEEEEEEEEE
// 	exit(exit_code);
// }
