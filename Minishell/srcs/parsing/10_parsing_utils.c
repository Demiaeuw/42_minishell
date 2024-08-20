/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:39:51 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/20 18:51:59 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Fonction utilitaire de la gestion du parsing
 * 1. Affichage de la liste.
 * 2. Free de la liste.
 * 3. Free du tableau de tableau
 */
void	print_token_list(t_token *head)
{
	t_token	*current;
	char	*is_builtin_str;
	char	*is_last_command_str;
	int		i;

	i = 1;
	current = head;
	while (current != NULL)
	{
		if (current->is_builtin)
			is_builtin_str = "Yes";
		else
			is_builtin_str = "No";
		if (current->is_last_command)
			is_last_command_str = "Yes";
		else
			is_last_command_str = "No";
		printf("\nt_token node n° %d\n", i);
		printf("Value: %s\n", current->value);
		printf("Type: %d\n", current->type);
		printf("Is Builtin: %s\n", is_builtin_str);
		printf("Builtin Info: %s\n", current->builtin_info);
		printf("Is Last Command: %s\n", is_last_command_str);
		print_chevron_node(current);
		printf("---------------------------------------------\n");
		i++;
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

void	free_token_array(char **tokenarray)
{
	int	i;

	i = 0;
	if (!tokenarray)
		return ;
	while (tokenarray[i] != NULL)
	{
		free(tokenarray[i]);
		i++;
	}
	free(tokenarray);
}

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}
