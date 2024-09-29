/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:57:36 by acabarba          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/09/30 00:03:02 by yonieva          ###   ########.fr       */
=======
/*   Updated: 2024/09/29 22:39:34 by gaesteve         ###   ########.fr       */
>>>>>>> 26026b7059bd359696a83a6a5a7510a3f5150ddd
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	g_shell_mode = 0;

void	init_mask(struct sigaction *sig)
{
	sigemptyset(&sig->sa_mask);
	sigaddset(&sig->sa_mask, SIGINT);
	sigaddset(&sig->sa_mask, SIGQUIT);
}

void	init_sigaction(struct sigaction *sig)
{
	sigaction(SIGINT, sig, NULL);
	sig->sa_handler = SIG_IGN;
	sigaction(SIGQUIT, sig, NULL);
}

void	init_signal()
{
	struct sigaction	sig;

	ft_memset(&sig, 0, sizeof(struct sigaction));
	init_mask(&sig);
	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = &signal_handler;
	init_sigaction(&sig);
}

void	signal_handler(int signum, siginfo_t *siginfo, void *context)
{
	(void)siginfo;
	(void)context;

	if (signum == SIGINT)
	{
		if (g_shell_mode == 0)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			write(1, "\n", 1);
			rl_redisplay();
		}
		else if (g_shell_mode == 1)
			write(1, "\n", 1);
		else if (g_shell_mode == 2)
		{
			write(1, "\n", 1);
			close(STDIN_FILENO);
			//g_shell_mode = 0;
		}
	}
}

pid_t	fork_and_execute(char *cmd_path, char **split_args, t_envp *envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTERM, SIG_DFL);
		execute_child_process(cmd_path, split_args, envp);
	}
	else if (pid > 0)
	{
		g_shell_mode = 1;
		waitpid(pid, &status, 0);
		g_shell_mode = 0;
		if (WIFEXITED(status))
			envp->status_cmd = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			envp->status_cmd = 128 + WTERMSIG(status);
	}
	else
	{
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	return (pid);
}
