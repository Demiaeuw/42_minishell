/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   31_parse_chevron.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:30:29 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/16 14:55:6 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_chevron(t_token *token, char **ptr, char *start,
			t_chevron **last_text_node)
{
	t_chevron_type	type;

	if (**ptr == '>')
		type = OUT;
	else
		type = IN;
	if (*(*ptr + 1) == '>')
	{
		type = DOUBLE_OUT;
		(*ptr)++;
	}
	else if (*(*ptr + 1) == '<')
	{
		type = DOUBLE_IN;
		(*ptr)++;
	}
	append_chevron_node(&(token->file_in_out),
		create_chevron_node(true, type, strndup(start, *ptr - start + 1)));
	(*ptr)++;
	*last_text_node = NULL;
}

void	handle_text(t_token *token, char *start, char **ptr,
			t_chevron **last_text_node)
{
	char	*temp_value;
	char	*new_value;
	char	*temp;

	while (**ptr && **ptr != ' ' && **ptr != '>' && **ptr != '<')
		(*ptr)++;
	temp_value = strndup(start, *ptr - start);
	if (*last_text_node)
	{
		new_value = ft_strjoin((*last_text_node)->value, " ");
		temp = ft_strjoin(new_value, temp_value);
		free((*last_text_node)->value);
		(*last_text_node)->value = temp;
		free(new_value);
		free(temp_value);
	}
	else
	{
		*last_text_node = create_chevron_node(false, 0, temp_value);
		append_chevron_node(&(token->file_in_out), *last_text_node);
	}
}

void	check_and_free_file_in_out(t_token *token, bool found_chevron)
{
	if (!found_chevron && token->file_in_out)
	{
		free(token->file_in_out);
		token->file_in_out = NULL;
	}
}

void	parse_chevrons(t_token *token)
{
	char			*ptr;
	char			*start;
	t_chevron		*last_text_node;
	bool			found_chevron;

	ptr = token->value;
	last_text_node = NULL;
	found_chevron = false;
	while (*ptr)
	{
		while (*ptr == ' ')
			ptr++;
		start = ptr;
		if (*ptr == '>' || *ptr == '<')
		{
			found_chevron = true;
			handle_chevron(token, &ptr, start, &last_text_node);
		}
		else
			handle_text(token, start, &ptr, &last_text_node);
	}
	check_and_free_file_in_out(token, found_chevron);
}
