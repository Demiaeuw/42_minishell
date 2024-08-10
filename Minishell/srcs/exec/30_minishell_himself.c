/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_minishell_himself.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 20:16:46 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/10 20:28:52 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void launch_minishell(char **env)
{
    pid_t pid;
    char *args[] = {"./minishell", NULL};
    
    // Fork the process
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) 
	{ // Child process
        execve(args[0], args, env); // Replace process image with minishell
        perror("execve"); // If execve fails
        exit(EXIT_FAILURE);
    } else 
	{ // Parent process
        waitpid(pid, NULL, 0); // Wait for the child process to finish
    }
}
