/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_spliting_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:59:29 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/14 12:31:48 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*extract_token(const char *str, int start, int len)
{
	return (ft_strndup(str + start, len));
}

static int	handle_quote(char c, bool *in_quotes, char *quote_char)
{
	if ((c == '"' || c == '\'') && (!*in_quotes || *quote_char == c))
	{
		if (*in_quotes)
		{
			*in_quotes = 0;
			*quote_char = '\0';
		}
		else
		{
			*in_quotes = 1;
			*quote_char = c;
		}
	}
	return (*in_quotes);
}

static char	**process_split(const char *str, char **result, int *count)
{
	int		i;
	int		start;
	bool	in_quotes;
	char	quote_char;

	i = 0;
	start = 0;
	in_quotes = false;
	quote_char = '\0';
	while (str[i])
	{
		handle_quote(str[i], &in_quotes, &quote_char);
		if ((str[i] == '|' && !in_quotes) || str[i + 1] == '\0')
		{
			result[*count] = extract_token(str, start, i - start
					+ (str[i + 1] == '\0'));
			if (!result[(*count)++])
				return (free_tokens(result), NULL);
			start = i + 1;
		}
		i++;
	}
	return (result);
}

char	**ft_split_quoted(const char *str)
{
	char	**result;
	int		count;

	count = 0;
	result = safe_malloc(sizeof(char *) * (strlen(str) / 2 + 2));
	if (!result)
		return (NULL);
	if (!process_split(str, result, &count))
		return (NULL);
	result[count] = NULL;
	return (result);
}
