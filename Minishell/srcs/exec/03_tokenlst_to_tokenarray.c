/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_tokenlst_to_tokenarray.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 21:53:51 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/12 23:40:53 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**free_token(char **str, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

int	count_token(t_token *token)
{
	int		count;
	t_token	*current;

	count = 0;
	current = token;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	**convert_token(t_token *token)
{
	t_token	*current;
	char	**str;
	int		count;
	int		i;

	count = 0;
	current = token;
	while (current && current->type != TOKEN_PIPE)
	{
		count++;
		current = current->next;
	}
	str = (char **)safe_malloc((count + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	i = 0;
	current = token;
	while (current && current->type != TOKEN_PIPE)
	{
		str[i] = ft_strdup(current->value);
		i++;
		current = current->next;
	}
	str[i] = NULL;
	return (str);
}
