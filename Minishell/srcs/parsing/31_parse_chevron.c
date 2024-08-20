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

void	handle_chevron(t_token *token, char **ptr, char *start)
{
	t_chevron_type	type;
	char			*value;

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
	(*ptr)++;
	while (**ptr == ' ')
		(*ptr)++;
	start = *ptr;
	while (**ptr && **ptr != ' ' && **ptr != '>' && **ptr != '<')
		(*ptr)++;
	value = strndup(start, *ptr - start);
	append_chevron_node(&(token->file_in_out),
		create_chevron_node(type, value));
}

void	handle_command(t_token *token, char *start, char **ptr)
{
	char			*value;

	while (**ptr && **ptr != ' ' && **ptr != '>' && **ptr != '<')
		(*ptr)++;
	value = strndup(start, *ptr - start);
	append_chevron_node(&(token->file_in_out),
		create_chevron_node(COMMAND, value));
}

void	main_parse_chevrons(t_token *tokens)
{
	t_token	*current_token;

	current_token = tokens;
	while (current_token)
	{
		if (current_token->type != TOKEN_PIPE)
		{
			parse_chevrons(current_token);
		}
		current_token = current_token->next;
	}
}

void	parse_chevrons(t_token *token)
{
	char			*ptr;
	char			*start;
	t_chevron		*last_command_node;
	bool			found_chevron;

	ptr = token->value;
	last_command_node = NULL;
	found_chevron = false;
	while (*ptr)
	{
		while (*ptr == ' ')
			ptr++;
		start = ptr;
		if (*ptr == '>' || *ptr == '<')
		{
			if (last_command_node)
			{
				append_chevron_node(&(token->file_in_out), last_command_node);
				last_command_node = NULL;
			}
			handle_chevron(token, &ptr, start);
			found_chevron = true;
		}
		else
		{
			while (*ptr && *ptr != ' ' && *ptr != '>' && *ptr != '<')
				ptr++;
			if (!last_command_node)
				last_command_node = create_chevron_node(COMMAND, strndup(start, ptr - start));
			else
			{
				char *temp_value = ft_strjoin(last_command_node->value, " ");
				char *new_value = ft_strjoin(temp_value, strndup(start, ptr - start));
				free(last_command_node->value);
				last_command_node->value = new_value;
				free(temp_value);
			}
		}
	}
	if (found_chevron && last_command_node)
		append_chevron_node(&(token->file_in_out), last_command_node);
}
