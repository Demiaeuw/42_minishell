/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:52:26 by gaesteve          #+#    #+#             */
/*   Updated: 2024/07/24 15:55:29 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"

//simple str_cat rien de special
// char	*ft_strcat(char *dest, char *src)
// {
// 	char	*temp;

// 	if (!src)
// 		return (dest);
// 	temp = dest;
// 	while (*dest)
// 		dest++;
// 	while (*src)
// 	{
// 		*dest = *src;
// 		dest++;
// 		src++;
// 	}
// 	*dest = 0;
// 	return (temp);
// }

//Concatene 3 string de char grace a strcat au dessus
char	*str3join(char *str1, char *str2, char *str3)
{
	size_t	str1len;
	size_t	str2len;
	size_t	str3len;
	char	*returnstr;

	str3len = ft_strlen(str3);
	str1len = ft_strlen(str1);
	str2len = ft_strlen(str2);
	returnstr = (char *)ft_malloc(str1len + str2len + str3len + 1);
	if (!returnstr)
		return (0);
	returnstr[0] = 0;
	ft_strcat(returnstr, str1);
	ft_strcat(returnstr, str2);
	ft_strcat(returnstr, str3);
	return (returnstr);
}

/*
Convertit la liste chainee (envp_list) en un tableau de pointeurs de chaines
de caracteres (envpstr).
On parcout la liste et on utilise str3join juste au dessus pour creer les
elements du tableau.
*/
char	**envp_convert(t_envlist *envp_list)
{
	size_t	i;
	size_t	envplen;
	char	**envpstr;
	t_node	*node;
	t_envp	*envp_node;

	envplen = list_size(envp_list);
	envpstr = (char **)ft_malloc(sizeof(char *) * (envplen + 1));
	node = list_peek_first_node(envp_list);
	i = 0;
	while (node->next != 0)
	{
		envp_node = (t_envp *)node->content;
		envpstr[i] = str3join(envp_node->key, "=", envp_node->value);
		node = node->next;
		i++;
	}
	envpstr[i] = NULL;
	return (envpstr);
}

//juste une fonction pour verif si la var d env avec la key existe dans notre
//liste (envp_list).
int	envp_exist(t_envlist *envp_list, char *key)
{
	t_node	*node;

	node = list_peek_first_node(envp_list);
	while (node->next)
	{
		if (!ft_strcmp(((t_envp *)node->content)->key, key))
			return (1);
		node = node->next;
	}
	return (0);
}
