/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:49:03 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/14 21:19:26 by yonieva          ###   ########.fr       */
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
 void   parse_chevrons(t_token *tokens)
{
    t_token *current_token = tokens;
    t_token *command_token = NULL;

    while (current_token)
    {
        if (current_token->type == TOKEN_COMMAND)
        {
            command_token = current_token;
        }
        else if (strcmp(current_token->value, "<") == 0 || strcmp(current_token->value, "<<") == 0 ||
                 strcmp(current_token->value, ">") == 0 || strcmp(current_token->value, ">>") == 0)
        {
            if (command_token)
            {
                t_chevron *new_chevron = malloc(sizeof(t_chevron));
                if (!new_chevron)
                {
                    perror("Malloc failed");
                    exit(EXIT_FAILURE);
                }

                if (strcmp(current_token->value, "<") == 0)
                    new_chevron->type = IN;
                else if (strcmp(current_token->value, "<<") == 0)
                    new_chevron->type = DOUBLE_IN;
                else if (strcmp(current_token->value, ">") == 0)
                    new_chevron->type = OUT;
                else if (strcmp(current_token->value, ">>") == 0)
                    new_chevron->type = DOUBLE_OUT;

                new_chevron->file_name = strdup(current_token->next->value);
                new_chevron->is_last_open = false;
                new_chevron->is_last_closed = false;
                new_chevron->next = command_token->file_in_out;
                command_token->file_in_out = new_chevron;

                // Ignorer le fichier associé au chevron
                current_token = current_token->next;
            }
        }
        current_token = current_token->next;
    }
}