/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:19:00 by toto              #+#    #+#             */
/*   Updated: 2024/06/11 21:41:02 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	**check_full_wildcard(char **tab_current_file, int i)
{
	char	**tab_current_file2;

	tab_current_file2 = get_current_file();
	if (tab_current_file2[0])
		tab_current_file = fusionner_tableaux(tab_current_file,
				tab_current_file2, i);
	else
		free(tab_current_file2);
	return (tab_current_file);
}

char	**check_leading_wildcard(char **tab_current_file, int i)
{
	char	**tab_current_file2;

	tab_current_file2 = get_current_file_after(tab_current_file[i]
			+ only_char(tab_current_file[i] + 1, '*') + 1);
	if (tab_current_file2[0])
		tab_current_file = fusionner_tableaux(tab_current_file,
				tab_current_file2, i);
	else
		free(tab_current_file2);
	return (tab_current_file);
}

char	**check_middle_wildcard(char **tab_current_file, int i, int j)
{
	char	**tab_current_file2;
	char	*tmp;

	tmp = ft_substr(tab_current_file[i], 0, j);
	tab_current_file2 = get_current_file_after_before(tab_current_file[i] + j
			+ only_char(tab_current_file[i] + 1, '*'),
			tmp);
	if (tab_current_file2[0])
		tab_current_file = fusionner_tableaux(tab_current_file,
				tab_current_file2, i);
	else
		free(tab_current_file2);
	free(tmp);
	return (tab_current_file);
}

char	**handle_wildcard(char **tab_current_file, int i, int j)
{
	if (only_char(tab_current_file[i], '*') == ft_strlen(tab_current_file[i])
		&& tab_current_file[i][0] == '*')
	{
		return (check_full_wildcard(tab_current_file, i));
	}
	else if (tab_current_file[i][j] == '*' && j == 0)
	{
		return (check_leading_wildcard(tab_current_file, i));
	}
	else if (tab_current_file[i][j] == '*')
	{
		return (check_middle_wildcard(tab_current_file, i, j));
	}
	return (tab_current_file);
}

char	**check_wildcard(char **split_nodeValue)
{
	int		i;
	int		j;
	char	**tab_current_file;

	i = 0;
	j = -1;
	tab_current_file = split_nodeValue;
	while (tab_current_file[i])
	{
		while (tab_current_file[i][++j])
		{
			tab_current_file = handle_wildcard(tab_current_file, i, j);
		}
		j = -1;
		i++;
	}
	return (tab_current_file);
}
