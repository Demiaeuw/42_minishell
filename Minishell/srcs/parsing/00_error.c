/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:38:11 by acabarba          #+#    #+#             */
/*   Updated: 2024/07/17 16:23:24 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	main_error(void (*f)())
{
	f();
	exit(EXIT_FAILURE);
}

void	argument_error(void)
{
	ft_printf("\033[33m\n🚨Error !🚨\n\nArgument issue\n\n");
	return ;
}

void ft_error(int index)
{
    if (index == 1)
        printf("\033[33m🚨Commande invalide (par exemple)🚨\n");
    if (index == 2)
        printf("\033[33m🚨??🚨\n");
    if (index == 3)
        printf("\033[33m🚨??🚨\n");
    if (index == 4)
        printf("\033[33m🚨??🚨\n");
    if (index == 5)
        printf("\033[33m🚨??🚨\n");
    if (index == 6)/*message d erreur gere avant appel vous appellez le 6*/
        return (exit(EXIT_FAILURE));
    return (exit(EXIT_FAILURE));
}