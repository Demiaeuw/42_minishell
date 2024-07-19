/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:39:59 by acabarba          #+#    #+#             */
/*   Updated: 2024/07/19 17:40:19 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	// Trouver la fin de la chaîne dest
	while (dest[i])
		i++;
	// Ajouter chaque caractère de src à la fin de dest
	j = 0;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	// Ajouter le caractère nul à la fin de dest
	dest[i + j] = '\0';
	return (dest);
}
