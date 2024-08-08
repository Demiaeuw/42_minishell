/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:38:11 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/08 19:53:15 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
//                           vide normalement(test durant unset)
void	main_error(void (*f)(int), int index)
{
	f(index);
	exit(EXIT_FAILURE);
}

void	ft_error(int index)
{
	if (index == 1)
		printf("\033[33m\n🚨Error !🚨\n\nArgument issue\n\n\033[0m");
	if (index == 2)
		printf("\033[33m\n🚨Error !🚨\n\n'getcwd' fonction issue\n\n\033[0m");
	if (index == 3)
		printf("\033[33m\n🚨Error !🚨\n\nMalloc allocation issue\n\n\033[0m");
	if (index == 4)
		printf("\033[33m\n🚨Error !🚨\n\n????\n\n\033[0m");
	if (index == 5)
		printf("\033[33m\n🚨Error !🚨\n\n????\n\n\033[0m");
	if (index == 6)
		return (exit(EXIT_FAILURE));
	return (exit(EXIT_FAILURE));
}
