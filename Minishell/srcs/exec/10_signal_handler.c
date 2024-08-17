/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:57:36 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/17 22:30:38 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Gestion du ctrl + c
 * initialiser dans le main
 * 1. Efface la ligne actuelle
 * 2. Positionne le curseur sur une nouvelle ligne
 * 3. Saute une ligne "\n"
 * 4. Redisplay de readline
 */
void	handle_sigint(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
	rl_redisplay();
}

// les CIGNO
