/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_tokenlst_to_tokenarray.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 21:53:51 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/11 00:17:07 by acabarba         ###   ########.fr       */
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
	int	count;
	t_token *current;

	count = 0;
	current = token;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return(count);
}

// char	**convert_token(t_token *token)
// {
// 	t_token	*current;
// 	char	**str;
// 	int		i;
// 	int		count;

// 	i = 0;
// 	current = token;
// 	count = count_token(token);
// 	str = (char **)malloc((count + 1) * sizeof (char *));
// 	if (!str)
// 		return (NULL);
// 	while (i < count)
// 	{
// 		str[i] = strdup(current->value);
// 		if (!str[i])
// 			return (free_token(str, i));
// 		current = current->next;
// 		i++;
// 	}
// 	str[count] = NULL;
// 	return (str);
// }

char	**convert_token(t_token *token)
{
	int		count;
	char	**args;
	t_token	*current;
	int		i;

	// Compte le nombre de tokens (commande + arguments)
	count = 0;
	current = token;
	while (current && current->type != TOKEN_PIPE)
	{
		count++;
		current = current->next;
	}

	// Alloue de la mémoire pour les arguments
	args = (char **)safe_malloc((count + 1) * sizeof(char *));
	if (!args)
		return (NULL);

	// Copie les valeurs des tokens dans le tableau
	i = 0;
	current = token;
	while (current && current->type != TOKEN_PIPE)
	{
		args[i] = ft_strdup(current->value);
		i++;
		current = current->next;
	}
	args[i] = NULL;

	return (args);
}
