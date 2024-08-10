/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 02:35:38 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/10 03:04:28 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_pipes(t_token *token, t_envfinal *env)
{
    int pipefd[2];
    pid_t pid1, pid2;

    if (pipe(pipefd) == -1) 
    {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    pid1 = fork();
    if (pid1 == 0) 
    { // Premier processus enfant - `echo`
        dup2(pipefd[1], STDOUT_FILENO); // Rediriger stdout vers l'écriture du pipe
        close(pipefd[0]); // Fermer la lecture du pipe
        close(pipefd[1]); // Fermer l'écriture du pipe
        if (builtin_check(token)) 
        {
            builtin_selector(token, env);
        } else {
            execute_execve(token);
        }
        exit(EXIT_SUCCESS);
    }

    pid2 = fork();
    if (pid2 == 0) 
    { // Deuxième processus enfant - `pwd`
        dup2(pipefd[0], STDIN_FILENO); // Rediriger stdin vers la lecture du pipe
        close(pipefd[1]); // Fermer l'écriture du pipe
        close(pipefd[0]); // Fermer la lecture du pipe
        if (builtin_check(token->next->next)) 
        {
            builtin_selector(token->next->next, env);
        } 
        else 
        {
            execute_execve(token->next->next);
        }
        exit(EXIT_SUCCESS);
    }

    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}
