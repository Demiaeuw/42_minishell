/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_malloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:48:28 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/12 14:50:52 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Fonction de création de Malloc avec la vérification 
 */
void	*safe_malloc(size_t bytes)
{
	void	*ptr;

	ptr = malloc(bytes);
	if (ptr == NULL)
		write(1, "Error : malloc\n\n", 17);
	return (ptr);
}
