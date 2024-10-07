/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:13:41 by acabarba          #+#    #+#             */
/*   Updated: 2024/10/08 00:31:21 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Ici ce sont les fonctions qui permettent d'envoyer le programme dans
 * les bonnes parties du code pour les builtins
 */
int	builtin_check(t_token *token)
{
	return (token->is_builtin);
}

void	builtin_selector(t_token *token, t_envp *envp)
{
	const char *output_file = NULL;
	if (!ft_strcmp("cd", token->builtin_info))
		exe_cd(token->value, envp);
	if (!ft_strcmp("echo", token->builtin_info))
	{
		if (token->file_in_out)
        {
			output_file = get_output_file(token->file_in_out); // Extraire le fichier de sortie
    		exe_echo(token->file_in_out->value, envp, output_file);
		}
		else
			exe_echo(token->value, envp, NULL);
	}
	else if (!ft_strcmp("env", token->builtin_info))
		mini_env(envp);
	else if (!ft_strcmp("export", token->builtin_info))
		exe_export(envp, token->value);
	else if (!ft_strcmp("unset", token->builtin_info))
		exe_unset(envp, token->value);
	else if (!ft_strcmp("pwd", token->builtin_info))
		exe_pwd(envp);
	else if (!ft_strcmp("exit", token->builtin_info))
		exe_exit(token->value, envp, token);
}

void	builtin_selector_chevron(t_token *token, t_envp *envp)
{
	int	saved_stdin;
	int	saved_stdout;
	const char *output_file = NULL;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (token->file_in_out)
		handle_redirections(token->file_in_out);
	if (!ft_strcmp("cd", token->builtin_info))
		exe_cd(token->file_in_out->value, envp);
	else if (!ft_strcmp("echo", token->builtin_info))
	{
		if (token->file_in_out)
        	output_file = get_output_file(token->file_in_out); // Extraire le fichier de sortie
    	exe_echo(token->file_in_out->value, envp, output_file);
	}
	else if (!ft_strcmp("env", token->builtin_info))
		mini_env(envp);
	else if (!ft_strcmp("export", token->builtin_info))
		exe_export(envp, token->file_in_out->value);
	else if (!ft_strcmp("unset", token->builtin_info))
		exe_unset(envp, token->file_in_out->value);
	else if (!ft_strcmp("pwd", token->builtin_info))
		exe_pwd(envp);
	else if (!ft_strcmp("exit", token->builtin_info))
		exe_exit(token->file_in_out->value, envp, token);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

const char *get_output_file(t_chevron *file_in_out) {
    t_chevron *current = file_in_out;
    while (current) {
        if (current->type == OUT || current->type == DOUBLE_OUT) {
            return current->value; // Retourne le nom du fichier de sortie
        }
        current = current->next;
    }
    return NULL; // Aucun fichier de sortie trouvé
}
