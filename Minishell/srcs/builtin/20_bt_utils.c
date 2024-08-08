/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_bt_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:42:03 by gaesteve          #+#    #+#             */
/*   Updated: 2024/08/08 19:07:03 by gaesteve         ###   ########.fr       */
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
		return(1);
	else
		return(0);
}

/*void	gestion_erreur_bt(char *cmd, char *word, int status)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	if (word)
		ft_putstr_fd(": ", 2);
	ft_putstr_fd(word, 2);
	if (status == MANY_ARG)
		ft_putstr_fd(": too many arguments\n", 2);
	else if (status == INVALID_ARG)
		ft_putstr_fd(": not a valid identifier\n", 2);
}*/
