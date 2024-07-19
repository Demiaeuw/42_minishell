/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:38:11 by acabarba          #+#    #+#             */
/*   Updated: 2024/07/19 17:07:35 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	main_error(void (*f)(), int index)
{
	f(index);
	//appel de clean up
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
	if (index == 6)/*message d erreur gere avant appel vous appellez le 6*/
		return (exit(EXIT_FAILURE));
	return (exit(EXIT_FAILURE));
}
