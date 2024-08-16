/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:49:03 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/16 12:44:52 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_chevron(t_token *tokens) 
{
	t_token *current_token = tokens;
	while (current_token) 
	{
		printf("Token (Type %d): %s\n", current_token->type, current_token->value);
		t_chevron *current_chevron = current_token->file_in_out;
		while (current_chevron) {
			printf("  Chevron: Type %d, File %s\n", current_chevron->type, current_chevron->file_name);
			current_chevron = current_chevron->next;
		}
		current_token = current_token->next;
	}
}


t_chevron	*create_chevron(t_chevron_type type, const char *file_name) 
{
	t_chevron *new_chevron;

	new_chevron = malloc(sizeof(t_chevron));
	if (!new_chevron) 
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	new_chevron->type = type;
	new_chevron->is_last_open = false;
	new_chevron->is_last_closed = false;
	new_chevron->file_name = strdup(file_name);
	new_chevron->next = NULL;
	return new_chevron;
}

void	append_chevron(t_token *token, t_chevron *chevron) 
{
	t_chevron *current;
	if (!token->file_in_out) 
	{
		token->file_in_out = chevron;
	} 
	else 
	{
		current = token->file_in_out;
		while (current->next) 
		{
			current = current->next;
		}
		current->next = chevron;
	}
}

