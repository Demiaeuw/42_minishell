/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 22:39:45 by gaesteve          #+#    #+#             */
/*   Updated: 2024/08/14 00:53:26 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

static int	count_tokens(const char *str, char delimiter)
{
	int	count;
	int	in_token;

	count = 0;
	in_token = 0;
	while (*str)
	{
		if (*str == delimiter)
			in_token = 0;
		else if (!in_token)
		{
			in_token = 1;
			count++;
		}
		str++;
	}
	return (count);
}

static char	*allocate_token(const char *start, size_t len)
{
	char	*token;

	token = (char *)malloc(len + 1);
	if (token)
	{
		strncpy(token, start, len);
		token[len] = '\0';
	}
	return (token);
}

static char	*get_next_token(const char **str, char delimiter)
{
	const char	*start;
	char		*token;
	size_t		len;

	while (**str == delimiter)
		(*str)++;
	if (**str == '\0')
		return (NULL);
	start = *str;
	while (**str && **str != delimiter)
		(*str)++;
	len = *str - start;
	token = allocate_token(start, len);
	while (**str == delimiter)
		(*str)++;
	return (token);
}

char	**split_command(const char *cmd)
{
	char		**args;
	int			count;
	int			i;
	const char	*cmd_ptr;
	char		*token;

	count = count_tokens(cmd, ' ');
	args = (char **)malloc((count + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	cmd_ptr = cmd;
	i = 0;
	token = get_next_token(&cmd_ptr, ' ');
	while (token != NULL)
	{
		args[i++] = token;
		token = get_next_token(&cmd_ptr, ' ');
	}
	args[i] = NULL;
	return (args);
}
