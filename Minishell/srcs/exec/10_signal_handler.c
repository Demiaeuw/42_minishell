/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:57:36 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/18 20:26:18 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	t_signal	*handler;

	(void)info;
	handler = (t_signal *)context;
	if (sig == SIGINT)
	{
		handler->sigint = 1;
		rl_replace_line("", 0);
		rl_on_new_line();
		write(1, "\n", 1);
		rl_redisplay();
	}
	else if (sig == SIGTERM)
	{
		handler->sigterm = 1;
		write(1, "Exit shell\n", 11);
		exit(0);
	}
}

void	init_signal_handlers(t_signal *handler)
{
	struct sigaction	sa;

	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, (void *)handler);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	sa.sa_sigaction = signal_handler;
	sigaction(SIGTERM, &sa, (void *)handler);
}
