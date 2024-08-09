/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_interface.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:57:02 by yonieva           #+#    #+#             */
/*   Updated: 2024/08/05 15:57:02 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	display_prompt(void)
{
	// printf("\033[1;34mM\033[1;31mi\033[1;32mn\033[1;33mi\033[1;34ms\033[1;35mh\033[1;36me\033[1;37ml\033[1;31ml\033[0m  🌟> ");
	write(STDOUT_FILENO, "minishell> ", 12);
}

char	*read_input(void)
{
	char *buffer = (char*)malloc(sizeof(char) * BUFFER_SIZE);
	ssize_t bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
	if (bytes_read < 0)
	{
		free(buffer);
		return NULL;
	}
	buffer[bytes_read] = '\0';
	return (buffer);
}
