/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_pasing_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:39:51 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/12 13:46:39 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Fonction utilitaire de la gestion du parsing
 * 1. Affichage de la liste.
 * 2. Free de la liste.
 * 3. Free du tableau de tableau
 */
void    print_token_list(t_token *head)
{
    t_token *current = head;

    while (current != NULL)
    {
        printf("Value: %s\n", current->value);
        printf("Type: %d\n", current->type);
        printf("Is Builtin: %s\n", current->is_builtin ? "Yes" : "No");
        printf("Builtin Info: %s\n", current->builtin_info);
        printf("Is Last Command: %s\n", current->is_last_command ? "Yes" : "No");
        printf("-----\n");
        current = current->next;
    }
}

void	free_token_list(t_token *token_list)
{
	t_token	*temp;

	while (token_list != NULL)
	{
		temp = token_list;
		token_list = token_list->next;

		if (temp->value)
			free(temp->value);

		if (temp->builtin_info)
			free(temp->builtin_info);

		free(temp);
	}
}

void free_token_array(char **tokenarray)
{
    int i = 0;

    if (!tokenarray)
        return;

    while (tokenarray[i] != NULL)
    {
        free(tokenarray[i]);
        i++;
    }

    free(tokenarray);
}

