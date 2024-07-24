/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:51:30 by gaesteve          #+#    #+#             */
/*   Updated: 2024/07/23 14:54:37 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dup(int fildes)
{
	int	ret;

	ret = dup(fildes);
	if (ret == -1)
	{
		perror("dup error occurred");
		exit(EXIT_FAILURE);
	}
	return(ret);
}
