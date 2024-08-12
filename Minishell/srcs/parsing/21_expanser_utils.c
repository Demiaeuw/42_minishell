/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relativ_to_absolute.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:46:46 by yonieva           #+#    #+#             */
/*   Updated: 2024/07/17 14:46:46 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/* ************************************************************************** */
bool	is_relativ_path(const char *path)
{
	return (path[0] != '/');
}
/* ************************************************************************** */
char	*get_absolute_path(const char *relative_path)
{
	(void)relative_path;
	printf("get_absolute_path");
	return ("test");
	// char	courant_path[PATH_MAX];
	// int		len;
	// char	*absolute_path;

	// if (getcwd(courant_path, sizeof(courant_path)) == NULL)
	// 	main_error(ft_error, 2);
	// len = ft_strlen(courant_path) + ft_strlen(relative_path) + 2;
	// absolute_path = safe_malloc(len);
	// ft_strcpy(absolute_path, courant_path);
	// ft_strcat(absolute_path, "/");
	// ft_strcat(absolute_path, relative_path);
	// return (absolute_path);
}
/* ************************************************************************** */
void	clean_path(char *path)
{
	(void)path;
	printf("clean_path");
	// char *absolute_path;

	// absolute_path = get_absolute_path(path);
	// if(absolute_path)
	// {
	// 	ft_strcpy(path, absolute_path);
	// 	free(absolute_path);
	// }
}
/* ************************************************************************** */     