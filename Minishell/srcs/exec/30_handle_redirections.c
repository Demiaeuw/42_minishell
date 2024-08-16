/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_handle_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 23:45:42 by gaesteve          #+#    #+#             */
/*   Updated: 2024/08/16 14:56:04 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int open_file(t_chevron *chevron)
{
    int fd;

    if (chevron->type == OUT)
        fd = open(chevron->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if (chevron->type == DOUBLE_OUT)
        fd = open(chevron->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else if (chevron->type == IN)
        fd = open(chevron->file_name, O_RDONLY);
    else if (chevron->type == DOUBLE_IN)
    {
        // Gestion des double chevrons d'entrée (heredoc) peut être ajoutée ici.
        fd = -1;  // Placeholder
    }
    else
        fd = -1;

    if (fd < 0)
        perror("open_file error");
    else
        printf("File %s opened successfully with fd %d\n", chevron->file_name, fd);

    return fd;
}

void	handle_redirections(t_token *token)
{
	t_chevron	*current;
	int			fd_in = -1;
	int			fd_out = -1;

	current = token->file_in_out;
	while (current)
	{
		if (current->type == IN || current->type == DOUBLE_IN)
		{
			if (fd_in != -1)
				close(fd_in);
			fd_in = open_file(current);
			if (fd_in == -1)
				return ;
			dup2(fd_in, STDIN_FILENO);
		}
		else if (current->type == OUT || current->type == DOUBLE_OUT)
		{
			if (fd_out != -1)
				close(fd_out);
			fd_out = open_file(current);
			if (fd_out == -1)
				return ;
			dup2(fd_out, STDOUT_FILENO);
		}
		current = current->next;
	}
}

char	*truncate_str_chevron(char *str)
{
	int		i;
	char	*new_str;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>'))
			break ;
		if (str[i] == '<' || str[i] == '>')
			break ;
		i++;
	}
	new_str = (char *)malloc(sizeof(char) * (i + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[i] && !(str[i] == '<' || str[i] == '>'))
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
