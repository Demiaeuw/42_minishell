/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_envlst_to_envarray.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 21:50:40 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/10 21:53:26 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
