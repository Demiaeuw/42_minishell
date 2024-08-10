/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_convert_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 19:43:29 by gaesteve          #+#    #+#             */
/*   Updated: 2024/08/10 20:20:30 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	**free_env(char **str, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return(NULL);
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

char	**convert_env(t_envfinal *env)
{
	int			i;
	int			count;
	t_envfinal	*env_list;
	char		**str;

	i = 0;
	env_list = env;
	count = count_env(env);
	str = malloc((count + 1) * sizeof(char *));
	if (!str)
		return(NULL);
	while (i < count)
	{
		str[i] = strdup(env_list->value);
		if (!str[i])
			return(free_env(str, i));
		env_list = env_list->next;
		i++;
	}
	str[i] = NULL;
	return (str);
}
