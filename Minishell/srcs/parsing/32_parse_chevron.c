/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   32_parse_chevron.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:08:51 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/22 16:37:44 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	find_chevron_in_str(char *current_position, char **tokens,
			t_chevron_data *data)
{
	int		i;
	char	*found;

	i = 0;
	while (i < 4)
	{
		found = strstr(current_position, tokens[i]);
		if (found && (data->chevron == NULL || found < data->chevron))
		{
			data->chevron = found;
			data->token_length = strlen(tokens[i]);
			data->token_index = i;
		}
		i++;
	}
}

void	parse_before_chevron(t_chevron_data *data)
{
	char	*command_part;

	if (*(data->current_position) != data->chevron)
	{
		command_part = strndup(*(data->current_position), data->chevron
				- *(data->current_position));
		if (*(data->last_command_node) == NULL && *command_part != '\0')
		{
			append_chevron(data->head, COMMAND, command_part);
			*(data->last_command_node) = *(data->head);
		}
		free(command_part);
	}
	*(data->current_position) = data->chevron;
}

void	parse_after_chevron(t_chevron_data *data)
{
	char	*end_of_value;
	char	*value_part;

	*(data->current_position) = data->chevron + data->token_length;
	while (**(data->current_position) == ' ')
		(*(data->current_position))++;
	end_of_value = ft_strchr(*(data->current_position), ' ');
	if (end_of_value == NULL)
		end_of_value = *(data->current_position)
			+ ft_strlen(*(data->current_position));
	value_part = ft_strndup(*(data->current_position), end_of_value
			- *(data->current_position));
	append_chevron(data->head, data->types[data->token_index], value_part);
	free(value_part);
	*(data->current_position) = end_of_value;
}
