/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:13:41 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/10 20:56:27 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	main_builtin(t_token *token, t_envfinal *env)
{
	t_token	*current;

	current = token;
	while (current != NULL)
	{
		if (current->type == TOKEN_COMMAND || current->type == TOKEN_PIPE)
		{
			if (builtin_check(current))
				builtin_selector(current, env);
			else
				other_command(current, env);
		}
		current = current->next;
	}
}

int	builtin_check(t_token *token)
{
	return (token->is_builtin);
}

void	builtin_selector(t_token *token, t_envfinal *env)
{
	if (ft_strcmp("cd", token->builtin_info) == 0)
		exe_cd(token->value, env);
	else if (ft_strcmp("echo", token->builtin_info) == 0)
	{
		// token->value = expend_variable(token->value, env);
		exe_echo(token->value);
	}
	else if (!ft_strcmp("env", token->builtin_info))
		mini_env(env);
	else if (!ft_strcmp("export", token->builtin_info))
		exe_export(env, token);
	else if (!ft_strcmp("unset", token->builtin_info))
		exe_unset(&env, token);
	else if (!ft_strcmp("pwd", token->builtin_info))
		exe_pwd();
	else if (!ft_strcmp("exit", token->builtin_info))
		exe_exit(token->value, env, token);
	//debut de test
	//fin de test
		
	else
		printf("c'est un builtin mais tu la pas gerer connard\n");
}

void	other_command(t_token *token, t_envfinal *env)
{
	char	**envarray;
	if (ft_strcmp(token->builtin_info, "ls") == 0)
		exe_ls();
	else if (!ft_strcmp("./minishell", token->value))
	{
		envarray = convert_env(env);
		launch_minishell(envarray);
		return ;
	}
	else if (!ft_strcmp("clear", token->builtin_info))
        exe_clear();
	else 
	execute_execve(token, env);
}






// Debut de test
char	**convert_env(t_envfinal *env)
{
	int			i;
	int			count;
	t_envfinal	*current;
	char		**str;
	char		*env_entry;

	i = 0;
	current = env;
	count = count_env(env);
	str = malloc((count + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	while (i < count && current)
	{
		// Concaténer le type et le contenu de l'environnement avec un '=' entre les deux
		env_entry = malloc(strlen(current->type) + strlen(current->content) + 2);
		if (!env_entry)
			return (free_env(str, i));
		strcpy(env_entry, current->type);
		strcat(env_entry, "=");
		strcat(env_entry, current->content);

		str[i] = env_entry;
		if (!str[i])
			return (free_env(str, i));
		current = current->next;
		i++;
	}
	str[i] = NULL;
	return (str);
}

char	**free_env(char **str, int count)
{
	int	i;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < count)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}


int	count_env(t_envfinal *env)
{
	int	count;
	t_envfinal *current;

	count = 0;
	current = env;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}


// fin de test