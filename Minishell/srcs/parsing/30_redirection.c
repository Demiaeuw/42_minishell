/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:49:03 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/15 21:21:56 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Gestion des redirections
 * 
 * Il faut init la struct t_chevron et la remplir avec des valeurs de bases.
 * Il faut attribué la pointeur vers cette nouvelle liste chainé t_chevron chaque noeud de t_token.
 * Parsing de token->value pour repéré les chevron et les attribué comme ils devraient avec l'enum
 * 
 */

/* Fonction pour afficher les tokens et leurs chevrons associés
static void print_chevron(t_token *tokens) 
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
}*/


static t_chevron	*create_chevron(t_chevron_type type, const char *file_name) 
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

static void	append_chevron(t_token *token, t_chevron *chevron) 
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

void	parse_chevrons_and_files(t_token *tokens) 
{
	t_token *current_token = tokens;

	while (current_token) 
	{
		char *value = current_token->value;
		char *ptr = value;

		while (*ptr) 
		{
			if (*ptr == '>') 
			{
				t_chevron_type type = OUT;
				ptr++;
				if (*ptr == '>') 
				{
					type = DOUBLE_OUT;
					ptr++;
				}
				while (*ptr == ' ') ptr++;
				char *file_start = ptr;
				while (*ptr && *ptr != ' ' && *ptr != '>' && *ptr != '<') ptr++;
				char *file_name = strndup(file_start, ptr - file_start);
				append_chevron(current_token, create_chevron(type, file_name));
				free(file_name);
			} 
			else if (*ptr == '<') 
			{
				t_chevron_type type = IN;
				ptr++;
				if (*ptr == '<') 
				{
					type = DOUBLE_IN;
					ptr++;
				}
				while (*ptr == ' ') ptr++;
				char *file_start = ptr;
				while (*ptr && *ptr != ' ' && *ptr != '>' && *ptr != '<') ptr++;
				char *file_name = strndup(file_start, ptr - file_start);
				append_chevron(current_token, create_chevron(type, file_name));
				free(file_name);
			} 
			else 
				ptr++;
		}
		current_token = current_token->next;
	}
	//print_chevron(tokens); 
}

