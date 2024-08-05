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

void display_prompt(void)
{
    write(STDOUT_FILENO, "minishell> ", 12);
}



char *read_input(void)
{
    //MALLOC A FREE
    char *buffer = malloc(BUFFER_SIZE);
    if (!buffer)
    {
        write(STDERR_FILENO, "Memory allocation error\n", 24);
        return NULL;
    }
    ssize_t bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
    if (bytes_read < 0)
    {
        free(buffer);
        return NULL;
    }
    buffer[bytes_read] = '\0';
    return buffer;
}


