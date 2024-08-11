/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_mini_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 13:24:23 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/11 13:24:23 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_target_path(char **tab, char **env)
{
	char	*path;
	char	*pwd;

	if (len_tab(tab) > 1)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (NULL);
	}
	else if (len_tab(tab) == 1)
	{
		if (tab[0][0] != '/')
		{
			pwd = get_cwd(0);
			path = ft_strjoin(pwd, ft_strdup("/"));
			path = ft_strjoin(path, ft_strdup(tab[0]));
		}
		else
			path = ft_strdup(tab[0]);
	}
	else
		path = get_env_value("HOME", env);
	return (path);
}