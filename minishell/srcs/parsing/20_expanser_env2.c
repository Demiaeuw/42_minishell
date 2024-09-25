/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_expanser_env2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:34:04 by acabarba          #+#    #+#             */
/*   Updated: 2024/09/25 17:57:51 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	process_token_values(t_token *token, char **env)
{
	t_token	*current;
	char	*expanded_value;

	current = token;
	if (token->is_builtin == true)
	{
		while (current != NULL)
		{
			expanded_value = expand_variables_in_value(current->value, env);
			free(current->value);
			current->value = expanded_value;
			current = current->next;
		}
	}
}

void	insert_string_into_result(t_exp_data *data, const char *str)
{
	while (*str)
	{
		data->result[data->j++] = *str++;
	}
}
