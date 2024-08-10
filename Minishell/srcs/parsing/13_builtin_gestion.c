/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13_builtin_gestion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:13:23 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/10 03:12:26 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	copy_com(const char *src, char *dest)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i] && ft_is_not_alpha(src[i]))
		i++;
	while (src[i] && ft_isalpha(src[i]))
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
}

bool	is_builtin_command(char *com)
{
	return (!strcmp(com, "cd") || !strcmp(com, "echo") || !strcmp(com, "pwd")
		|| !strcmp(com, "env") || !strcmp(com, "export")
		|| !strcmp(com, "unset") || !strcmp(com, "exit")
		|| !strcmp(com, "clear"));
}

void	add_builtin(t_token *token)
{
	t_token	*current;
	char	com[256];

	current = token;
	while (current)
	{
		if (current->type == TOKEN_COMMAND)
		{
			copy_com(current->value, com);
			if (is_builtin_command(com))
				current->is_builtin = true;
			ft_strcpy(current->builtin_info, com);
		}
		current = current->next;
	}
}
