/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:49:03 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/18 00:22:31 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_chevron(t_token *tokens)
{
	t_token		*current_token;
	t_chevron	*current_chevron;

	current_token = tokens;
	while (current_token)
	{
		printf("Token (Type %d): %s\n", current_token->type,
			current_token->value);
		current_chevron = current_token->file_in_out;
		while (current_chevron)
		{
			printf("  Chevron: Type %d, File %s\n", current_chevron->type,
				current_chevron->file_name);
			current_chevron = current_chevron->next;
		}
		current_token = current_token->next;
	}
}

t_chevron	*create_chevron(t_chevron_type type, const char *file_name)
{
	t_chevron	*new_chevron;

	new_chevron = malloc(sizeof(t_chevron));
	if (!new_chevron)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	new_chevron->type = type;
	new_chevron->is_last_open = false;
	new_chevron->is_last_closed = false;
	new_chevron->file_name = ft_strdup(file_name);
	new_chevron->clean_value = NULL;
	new_chevron->next = NULL;
	return (new_chevron);
}

void	append_chevron(t_token *token, t_chevron *chevron)
{
	t_chevron	*current;

	if (!token->file_in_out)
	{
		chevron->clean_value = extract_clean_value(token->value);
		token->file_in_out = chevron;
	}
	else
	{
		current = token->file_in_out;
		while (current->next)
			current = current->next;
		current->next = chevron;
	}
}

char	*extract_clean_value(char *str)
{
	int		i;
	char	*new_str;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '<' && str[i + 1] == '<')
			|| (str[i] == '>' && str[i + 1] == '>'))
			break ;
		if (str[i] == '<' || str[i] == '>')
			break ;
		i++;
	}
	new_str = (char *)malloc(sizeof(char) * (i + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[i] && !(str[i] == '<' || str[i] == '>'))
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
