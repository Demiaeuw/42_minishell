/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_expanser_env2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:34:04 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/17 19:11:26 by acabarba         ###   ########.fr       */
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
			if (!ft_strcmp(token->builtin_info, "echo"))
				expanded_value = clean_string(expanded_value);
			current->value = expanded_value;
			current = current->next;
		}
	}
}
