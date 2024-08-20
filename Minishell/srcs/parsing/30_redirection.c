/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:49:03 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/20 19:22:14 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


const char	*get_chevron_type_str(t_chevron_type type)
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



// c_c == chevron_check
t_chevron	*create_chevron_node(t_chevron_type type, char *value)
{
	t_chevron	*new_chevron;

	new_chevron = malloc(sizeof(t_chevron));
	if (!new_chevron)
		return (NULL);
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
