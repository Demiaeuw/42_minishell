/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 19:23:14 by acabarba          #+#    #+#             */
/*   Updated: 2024/07/17 15:22:07 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    *safe_malloc(size_t bytes)
{
    void *ptr;

    ptr = malloc(bytes);
    if (ptr == NULL)
    {
        printf("\033[33m🚨Erreur d allocation de memoire🚨\n");
        ft_error(6);
    }
    return(ptr);
}

void	free_token_value(void *value)
{
	free(value);
}

//exemple d'appel de cette fonction : free_token(&token, free_token_value)

void	free_token_list(t_token **lst, void (*del)(void*))
{
	t_token *current;
	t_token *next;

	if (!del || !lst || !*lst)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		del(current->value);
		free(current);
		current = next;
	}
	*lst = (NULL);
}
