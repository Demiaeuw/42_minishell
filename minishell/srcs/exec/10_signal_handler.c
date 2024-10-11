/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpourcel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:57:36 by acabarba          #+#    #+#             */
/*   Updated: 2024/10/09 19:22:07 by kpourcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	g_global_sig;

void	init_mask(struct sigaction *sig)
{
	sigemptyset(&sig->sa_mask);
	sigaddset(&sig->sa_mask, SIGINT);
	sigaddset(&sig->sa_mask, SIGQUIT);
}

void	init_sigaction(struct sigaction *sig)
{
	sig->sa_flags = SA_SIGINFO;
	sig->sa_sigaction = &signal_handler;
	sigaction(SIGINT, sig, NULL);
	sig->sa_handler = SIG_IGN;
	sigaction(SIGQUIT, sig, NULL);
}

void	init_signal(void)
{
	struct sigaction	sig;

	ft_memset(&sig, 0, sizeof(struct sigaction));
	init_mask(&sig);
	init_sigaction(&sig);
}

void	handle_sigint_cmd(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		g_global_sig = 130;
	}
}

void	signal_handler(int signum, siginfo_t *siginfo, void *context)
{
	(void)siginfo;
	(void)context;
	if (signum == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_redisplay();
		g_global_sig = 130;
	}
}
