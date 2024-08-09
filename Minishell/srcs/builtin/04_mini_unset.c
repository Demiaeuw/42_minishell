/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_mini_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:14:09 by gaesteve          #+#    #+#             */
/*   Updated: 2024/08/09 16:29:31 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*extract_key(t_token *token)
{
	char	*key;
	int		i;
	int		j;

	key = safe_malloc(ft_strlen(token->value) + 1);
	i = 0;
	j = 0;
	while (token->value[i] == ' ')
		i++;
	i += 5;
	while (token->value[i] == ' ')
		i++;
	while (token->value[i])
		key[j++] = token->value[i++];
	key[j] = '\0';
	return (key);
}

static void	remove_env_node(t_envfinal **env, t_envfinal *curt, t_envfinal *prv)
{
	if (!prv)
		*env = curt->next;
	else
		previous->next = curt->next;
	free(curt->type);
	free(curt->content);
	free(curt);
}

void	exe_unset(t_envfinal **env, t_token *token)
{
	t_envfinal	*current;
	t_envfinal	*previous;
	char		*key;

	if (!token || !env || !*env)
		return ;
	key = extract_key(token);
	current = *env;
	previous = NULL;
	while (current && ft_strcmp(current->type, key) != 0)
	{
		previous = current;
		current = current->next;
	}
	if (current)
		remove_env_node(env, current, previous);
	free(key);
}
