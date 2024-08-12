/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:59:39 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/12 14:00:12 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token *main_parsing(char *input)
{
    char    **tokenarray;
    t_token *token_list = NULL;
    t_token *new_node;
    t_token *pipe_node;
    int     i;

    tokenarray = ft_split_quoted(input);
    if (!tokenarray)
        return (NULL);

    i = 0;
    while (tokenarray[i])
    {
        // Nettoyer les espaces de la chaîne
        char *cleaned_value = clean_whitespace(tokenarray[i]);
        if (!cleaned_value)
        {
            free_token_list(token_list);
            free_token_array(tokenarray);
            return (NULL);
        }

        // Vérifier et fermer les guillemets si nécessaire
        char *final_value = close_quotes_if_needed(cleaned_value);
        free(cleaned_value); // Libérer la mémoire allouée pour la chaîne nettoyée

        if (!final_value)
        {
            free_token_list(token_list);
            free_token_array(tokenarray);
            return (NULL);
        }

        // Créez le nœud de commande avec la valeur finale
        new_node = create_command_node(final_value);
        free(final_value); // Libérez la chaîne finale après utilisation

        if (!new_node)
        {
            free_token_list(token_list);
            free_token_array(tokenarray);
            return (NULL);
        }
        add_token_node(&token_list, new_node);

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
    if (new_node != NULL)
        new_node->is_last_command = true;

    free_token_array(tokenarray);

    return (token_list);
}
