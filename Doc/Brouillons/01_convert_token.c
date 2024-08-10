/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_convert_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 19:36:52 by gaesteve          #+#    #+#             */
/*   Updated: 2024/08/10 23:10:29 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	**convert_token(t_token *token)
{
	t_token	*current;
	char	**str;
	int		i;
	int		count;

	i = 0;
	current = token;
	count = count_tokens(token);
	str = (char **)malloc((count + 1) * sizeof (char *));
	if (!str)
		return (NULL);
	while (i < count)
	{
		str[i] = strdup(current->value);
		if (!str[i])
			return (free_token(str, i));
		current = current->next;
		i++;
	}
	str[count] = NULL;
	return (str);
}