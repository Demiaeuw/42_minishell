/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 02:39:17 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/16 15:06:16 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	main_exec(t_token *token, t_envp *envp)
{
	t_token	*current;
	int		pipe;

	current = token;
	pipe = 0;
	while (current)
	{
		if (current->type == TOKEN_PIPE)
			pipe = 1;
		current = current->next;
	}
	if (pipe == 1)
		execute_pipes(token, envp);
	else if (token->file_in_out != NULL && token->file_in_out->clean_value != NULL)
		main_command_chevron(token, envp);
    else 
        main_command(token, envp);
}

void	main_command(t_token *token, t_envp *envp)
{
	t_token	*current;

	current = token;
	while (current != NULL)
	{
		if (current->type == TOKEN_COMMAND || current->type == TOKEN_PIPE)
		{
			if (builtin_check(current))
				builtin_selector(current, envp);
			else
				execute_execve(current, envp);
		}
		current = current->next;
	}
}

void	main_command_chevron(t_token *token, t_envp *envp)
{
    t_token	*current;
    int saved_stdin = dup(STDIN_FILENO);
    int saved_stdout = dup(STDOUT_FILENO);

    current = token;
    while (current != NULL)
    {
        if (current->type == TOKEN_COMMAND || current->type == TOKEN_PIPE)
        {
            // Appliquer les redirections
            handle_redirections(current);

            // Exécuter la commande après avoir redirigé STDOUT/STDIN
            if (builtin_check(current))
                builtin_selector_chevron(current, envp);
            else
                execute_execve(current, envp);

            // Restaurer les descripteurs d'origine après l'exécution de la commande
            dup2(saved_stdin, STDIN_FILENO);
            dup2(saved_stdout, STDOUT_FILENO);
        }
        current = current->next;
    }

    // Cleanup: Fermer les descripteurs de sauvegarde
    close(saved_stdin);
    close(saved_stdout);
}

