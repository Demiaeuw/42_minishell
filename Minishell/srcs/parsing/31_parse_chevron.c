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

void	handle_out_chevron(char **ptr, t_token *current_token)
{
	t_chevron_type	type;
	char			*file_start;
	char			*file_name;

	type = OUT;
	(*ptr)++;
	if (**ptr == '>')
	{
		type = DOUBLE_OUT;
		(*ptr)++;
	}
	while (**ptr == ' ')
		(*ptr)++;
	file_start = *ptr;
	while (**ptr && **ptr != ' ' && **ptr != '>' && **ptr != '<')
		(*ptr)++;
	file_name = ft_strndup(file_start, *ptr - file_start);
	append_chevron(current_token, create_chevron(type, file_name));
	free(file_name);
}

void	handle_in_chevron(char **ptr, t_token *current_token)
{
	t_chevron_type	type;
	char			*file_start;
	char			*file_name;

	type = IN;
	(*ptr)++;
	if (**ptr == '<')
	{
		type = DOUBLE_IN;
		(*ptr)++;
	}
	while (**ptr == ' ')
		(*ptr)++;
	file_start = *ptr;
	while (**ptr && **ptr != ' ' && **ptr != '>' && **ptr != '<')
		(*ptr)++;
	file_name = ft_strndup(file_start, *ptr - file_start);
	append_chevron(current_token, create_chevron(type, file_name));
	free(file_name);
}

void	parse_token_value(t_token *current_token)
{
	char	*ptr;

	ptr = current_token->value;
	while (*ptr)
	{
		if (*ptr == '>')
			handle_out_chevron(&ptr, current_token);
		else if (*ptr == '<')
			handle_in_chevron(&ptr, current_token);
		else
			ptr++;
	}
}

void	parse_chevrons_and_files(t_token *token)
{
	t_token	*current_token;

	current_token = token;
	while (current_token)
	{
		parse_token_value(current_token);
		current_token = current_token->next;
	}
}
