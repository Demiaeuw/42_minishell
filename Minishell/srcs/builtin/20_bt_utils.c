/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_bt_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:42:03 by gaesteve          #+#    #+#             */
/*   Updated: 2024/08/09 16:31:34 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_word_count(char **cmd_list)
{
	int	i;

	i = 0;
	while (cmd_list[i])
		i++;
	return (i);
}

int	get_env_len(char *line)
{
	int	length;

	length = 0;
	while (line[length] == '_' || ft_isalpha(line[length]))
		length++;
	if (length == 0)
		return (0);
	while (line[length] == '_' || \
			ft_isalpha(line[length]) || ft_isdigit(line[length]))
		length++;
	return (length);
}

int	is_proper_env(char *env_name)
{
	int	full_len;
	int	env_len;

	full_len = ft_strlen(env_name);
	env_len = get_env_len(env_name);
	if (full_len == env_len)
		return (1);
	else
		return (0);
}
