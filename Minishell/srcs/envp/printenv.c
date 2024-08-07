/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:07:32 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/07 16:07:41 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"

void	print_env_list(t_env *env)
{
	t_node *node;
	t_envp *env_var;

	node = list_peek_first_node(env);
	while (node)
	{
		env_var = (t_envp *)node->content;
		printf("%s=%s\n", env_var->key, env_var->value);
		node = node->next;
	}
}