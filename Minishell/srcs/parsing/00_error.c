/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:38:11 by acabarba          #+#    #+#             */
/*   Updated: 2024/07/11 15:48:50 by acabarba         ###   ########.fr       */
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
	ft_printf("\nError !\n\nArgument issue\n\n");
	return ;
}