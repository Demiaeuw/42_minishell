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

t_chevron* create_chevron(t_chevron_type type, const char *value) 
{
    t_chevron *chevron = (t_chevron*)malloc(sizeof(t_chevron));
    chevron->type = type;
    chevron->value = strdup(value);
    chevron->next = NULL;
    return chevron;
}

void append_chevron(t_chevron **head, t_chevron_type type, const char *value) 
{
    t_chevron *new_chevron = create_chevron(type, value);
    if (*head == NULL) {
        *head = new_chevron;
    } else {
        t_chevron *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_chevron;
    }
}

t_chevron* parse_string_chevron(char *str) 
{
    char *tokens[] = {">>", "<<", ">", "<"};
    t_chevron_type types[] = {DOUBLE_OUT, DOUBLE_IN, OUT, IN};
    t_chevron *head = NULL;
    t_chevron *last_command_node = NULL;
    
    char *current_position = str;
    
    while (*current_position) {
        char *chevron = NULL;
        int token_length = 0;
        int token_index = -1;
        
        // Trouver le premier chevron dans la chaîne
        for (int i = 0; i < 4; i++) {
            char *found = strstr(current_position, tokens[i]);
            if (found && (chevron == NULL || found < chevron)) {
                chevron = found;
                token_length = strlen(tokens[i]);
                token_index = i;
            }
        }
        
        if (chevron) { // Chevron trouvé
            if (current_position != chevron) {
                // Ajouter la partie commande avant le chevron
                char *command_part = strndup(current_position, chevron - current_position);
                if (last_command_node == NULL && *command_part != '\0') {
                    append_chevron(&head, COMMAND, command_part);
                    last_command_node = head;
                }
                free(command_part);
            }
            
            // Avancer après le chevron
            current_position = chevron + token_length;
            
            // Ignorer les espaces après le chevron
            while (*current_position == ' ') current_position++;
            
            // Trouver la fin de la valeur (jusqu'à un espace ou la fin de la chaîne)
            char *end_of_value = strchr(current_position, ' ');
            if (end_of_value == NULL) end_of_value = current_position + strlen(current_position);
            
            char *value_part = strndup(current_position, end_of_value - current_position);
            append_chevron(&head, types[token_index], value_part);
            free(value_part);
            
            current_position = end_of_value;
        } else {
            // Aucun autre chevron trouvé, ajouter le reste comme commande s'il y a une commande valide
            if (*current_position != '\0') {
                append_chevron(&head, COMMAND, current_position);
            }
            break;
        }
    }
    
    return head;
}



void free_chevron_list(t_chevron *head)
{
    t_chevron *tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp->value);
        free(tmp);
    }
}

// void print_chevron_list(t_chevron *head) 
// {
//     t_chevron *current = head;
//     while (current != NULL) {
//         printf("Type: %d, Value: %s\n", current->type, current->value);
//         current = current->next;
//     }
// }

char	*get_chevron_type_str(t_chevron_type type)
{
	if (type == IN)
		return ("IN");
	else if (type == DOUBLE_IN)
		return ("DOUBLE_IN");
	else if (type == OUT)
		return ("OUT");
	else if (type == DOUBLE_OUT)
		return ("DOUBLE_OUT");
	else
		return ("COMMAND");
}

void	print_chevron_node(t_token *token)
{
	t_chevron	*current_chevron;
	int			i;

	current_chevron = token->file_in_out;
	i = 1;
	while (current_chevron)
	{
		printf("\n	Node n°%d\n", i);
		printf("	Type : %s\n", get_chevron_type_str(current_chevron->type));
		printf("	Value: %s\n", current_chevron->value);
		printf("	-------------\n");
		current_chevron = current_chevron->next;
		i++;
	}
}

void	main_parse_string_chevron(t_token *token)
{
	t_token *current;

	current = token;
	while(current)
	{
		if (current->type == TOKEN_COMMAND)
			if(contains_chevrons(current->value))
				current->file_in_out = parse_string_chevron(current->value);
		current = current->next;
	}
 }

 int	contains_chevrons(const char *str) 
 {
    while (*str) 
	{
        if (*str == '<' || *str == '>') 
		{
            return 1;  // Chevron trouvé, on renvoie 1
        }
        str++;
    }
    return 0;  // Aucun chevron trouvé, on renvoie 0
}
