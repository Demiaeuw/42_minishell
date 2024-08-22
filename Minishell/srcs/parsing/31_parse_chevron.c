/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   31_parse_chevron.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:05:59 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/22 16:36:05 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// t_chevron	*parse_string_chevron(char *str)
// {
//     char *tokens[] = {">>", "<<", ">", "<"};
//     t_chevron_type types[] = {DOUBLE_OUT, DOUBLE_IN, OUT, IN};
//     t_chevron *head = NULL;
//     t_chevron *last_command_node = NULL;

//     char *current_position = str;

//     while (*current_position) {
//         char *chevron = NULL;
//         int token_length = 0;
//         int token_index = -1;

//         // Trouver le premier chevron dans la chaîne
//         for (int i = 0; i < 4; i++) {
//             char *found = strstr(current_position, tokens[i]);
//             if (found && (chevron == NULL || found < chevron)) {
//                 chevron = found;
//                 token_length = strlen(tokens[i]);
//                 token_index = i;
//             }
//         }

//         if (chevron) { // Chevron trouvé
//             if (current_position != chevron) {
//                 // Ajouter la partie commande avant le chevron
//                 char *command_part = strndup(current_position,
//						chevron - current_position);
//                 if (last_command_node == NULL && *command_part != '\0') {
//                     append_chevron(&head, COMMAND, command_part);
//                     last_command_node = head;
//                 }
//                 free(command_part);
//             }

//             // Avancer après le chevron
//             current_position = chevron + token_length;

//             // Ignorer les espaces après le chevron
//             while (*current_position == ' ') current_position++;

//             // Trouver la fin de la valeur (jusqu'à un espace ou la fin de la chaîne)
//             char *end_of_value = strchr(current_position, ' ');
//           if (end_of_value == NULL) 
//				end_of_value = current_position + strlen(current_position);

//             char *value_part = strndup(current_position, end_of_value - current_position);
//             append_chevron(&head, types[token_index], value_part);
//             free(value_part);

//             current_position = end_of_value;
//         } else {
//             // Aucun autre chevron trouvé, ajouter le reste comme commande s'il y a une commande valide
//             if (*current_position != '\0') {
//                 append_chevron(&head, COMMAND, current_position);
//             }
//             break;
//         }
//     }

//     return (head);
// }

t_chevron	*parse_string_chevron(char *str)
{
	t_chevron	*head;
	t_chevron	*last_command_node;
	char		*current_position;

	head = NULL;
	last_command_node = NULL;
	current_position = str;
	while (*current_position)
	{
		parse_chevron_token(&current_position, &head, &last_command_node);
		if (*current_position == '\0')
			break ;
	}
	return (head);
}

void	parse_chevron_token(char **current_position, t_chevron **head,
			t_chevron **last_command_node)
{
	char			*tokens[4];
	t_chevron_type	types[4];
	t_chevron_data	data;

	initialize_tokens_types(tokens, types);
	data.current_position = current_position;
	data.head = head;
	data.last_command_node = last_command_node;
	data.chevron = NULL;
	data.token_length = 0;
	data.token_index = -1;
	data.types = types;
	find_chevron_in_str(*current_position, tokens, &data);
	if (data.chevron)
		parse_before_chevron(&data);
	parse_after_chevron(&data);
}

void	initialize_tokens_types(char **tokens, t_chevron_type *types)
{
	tokens[0] = ">>";
	tokens[1] = "<<";
	tokens[2] = ">";
	tokens[3] = "<";
	types[0] = DOUBLE_OUT;
	types[1] = DOUBLE_IN;
	types[2] = OUT;
	types[3] = IN;
}
