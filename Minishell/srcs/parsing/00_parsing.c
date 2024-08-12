/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:59:39 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/12 16:37:02 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token    *main_parsing(char *input)
{
	char	**tokenarray;
	t_token	*token_list;
	t_token	*new_node;
	t_token	*pipe_node;
	int		i;

	token_list = NULL;
	tokenarray = ft_split_quoted(input);
	if (!tokenarray)
		return (NULL);
	i = 0;
	while (tokenarray[i])
	{
		if (!process_token(tokenarray[i], &token_list))
		{
			free_token_list(token_list);
			free_token_array(tokenarray);
			return (NULL);
		}
		if (tokenarray[i + 1] != NULL)
		{
			pipe_node = create_pipe_node();
			if (!pipe_node)
			{
				free_token_list(token_list);
				free_token_array(tokenarray);
				return (NULL);
			}
			add_token_node(&token_list, pipe_node);
		}
		i++;
	}
	finalize_parsing(&new_node, tokenarray);
	return (token_list);
}

int    process_token(char *token, t_token **token_list)
{
    char    *cleaned_value;
    char    *final_value;
    t_token *new_node;

    cleaned_value = clean_whitespace(token);
    if (!cleaned_value)
        return (0);
    final_value = close_quotes_if_needed(cleaned_value);
    free(cleaned_value);
    if (!final_value)
        return (0);
    new_node = create_command_node(final_value);
    free(final_value);
    if (!new_node)
        return (0);
    add_token_node(token_list, new_node);
    return (1);
}

void    finalize_parsing(t_token **new_node, char **tokenarray)
{
    if (*new_node != NULL)
        (*new_node)->is_last_command = true;
    free_token_array(tokenarray);
}
