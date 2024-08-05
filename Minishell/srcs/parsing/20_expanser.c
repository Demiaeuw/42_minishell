// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   12_expanser.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/07/24 11:19:26 by yonieva           #+#    #+#             */
// /*   Updated: 2024/07/24 11:19:26 by yonieva          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../include/minishell.h"

// void	expanser_commands(t_token token_list)
// {
// 	t_token	*new_list = token_list;
// 	char 	*expanded_value;
// 	char	*start;
// 	char	*end;

// 	while(new_list != NULL)
// 	{
// 		if(new_list->type == TOKEN_COMMAND)
// 		{
// 			char *expanded_value = expand_variable(new_list->value);
// 			if(expand_value)
// 			{
// 				if(new_list->is_builtin)
// 				{
// 					start = expanded_value;
// 					end = expanded_value;
// 					while(*end)
// 					{
// 						while(*start && (*start == ' ' || *start == '\t'))
// 							start++;
// 						end = start;
// 						while(*end && *end != ' ' && *end != '\t')
// 							end++;
// 					}
// 					if(is_relativ_path(start))
// 					{
// 						path_seg = strndup(start, end - start);
// 						if (path_seg)
// 						{
// 							ft_memcpy(start, path_seg, ft_strlen(path_seg));
// 							start += ft_strlen(path_seg);
// 							free(path_seg);
// 						}
// 					}
// 					start = end;
// 				}
// 				free(new_list->value);
// 				new_list->value = expanded_value;
// 			}
// 		}
// 		new_list = new_list->next;
// 	}
// }