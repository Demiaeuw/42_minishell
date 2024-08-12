/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_spliting_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:59:29 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/12 14:06:23 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	free_tokens(char **tokens)
{
	int i;

	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}

static char	*extract_token(const char *str, int start, int len)
{
	char	*token;

	token = ft_strndup(str + start, len);
	return (token);
}

static int	handle_quote(char c, bool *in_quotes, char *quote_char)
{
	if ((c == '"' || c == '\'') && (!*in_quotes || *quote_char == c))
	{
		*in_quotes = !(*in_quotes);
		*quote_char = *in_quotes ? c : '\0';
	}
	return (*in_quotes);
}

char	**ft_split_quoted(const char *str)
{
	char	**result;
	int		i, start, count;
	bool	in_quotes;
	char	quote_char;

	result = malloc(sizeof(char *) * (strlen(str) / 2 + 2));
	if (!result)
		return (NULL);
	i = 0, start = 0, count = 0, in_quotes = false, quote_char = '\0';
	while (str[i])
	{
		handle_quote(str[i], &in_quotes, &quote_char);
		if ((str[i] == '|' && !in_quotes) || str[i + 1] == '\0')
		{
			result[count] = extract_token(str, start, i - start + (str[i + 1] == '\0'));
			if (!result[count++])
				return (free_tokens(result), NULL);
			start = i + 1;
		}
		i++;
	}
	return (result[count] = NULL, result);
}
