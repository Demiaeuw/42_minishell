/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_mini_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:13:51 by yonieva           #+#    #+#             */
/*   Updated: 2024/07/30 11:13:51 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exe_pwd(void)
{
	char temp[1024];

	if (getcwd(temp, sizeof(temp)) == NULL)
        return 1;
	printf("%s\n", temp);
	return (0);
}
