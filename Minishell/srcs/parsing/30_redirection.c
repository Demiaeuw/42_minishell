/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:49:03 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/20 17:41:59 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_chevron_node(t_token *tokens)
{
	t_token		*current_token;
	t_chevron	*current_chevron;
	int			i;

	current_token = tokens;
	while (current_token)
	{
		current_chevron = current_token->file_in_out;
		i = 1;
		while (current_chevron)
		{
			printf("\n	Node n°%d\n", i);
			printf("	Est ce que c'est un chevron : %d\n",
				current_chevron->chevron_check);
			printf("	Chevron  de type: %d\n", current_chevron->type);
			printf("	Value: %s\n", current_chevron->value);
			printf("	-------------\n");
			current_chevron = current_chevron->next;
			i++;
		}
		current_token = current_token->next;
	}
}

// c_c == chevron_check
t_chevron	*create_chevron_node(bool c_c, t_chevron_type type, char *value)
{
	t_chevron	*new_chevron;

	new_chevron = malloc(sizeof(t_chevron));
	if (!new_chevron)
		return (NULL);
	new_chevron->chevron_check = c_c;
	new_chevron->type = type;
	new_chevron->value = value;
	new_chevron->next = NULL;
	return (new_chevron);
}

void	append_chevron_node(t_chevron **head, t_chevron *new_node)
{
	t_chevron	*current;

	if (!(*head))
		*head = new_node;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}
