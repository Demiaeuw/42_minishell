/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_handle_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 23:45:42 by gaesteve          #+#    #+#             */
/*   Updated: 2024/08/20 15:43:39 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int	open_file_in(t_chevron *chevron)
// {
// 	int	fd;

// 	fd = -1;
// 	if (chevron->type == IN)
// 		fd = open(chevron->file_name, O_RDONLY);
// 	else if (chevron->type == DOUBLE_IN)
// 		fd = -1;
// 	if (fd < 0)
// 		perror("open_file error");
// 	return (fd);
// }

// int	open_file_out(t_chevron *chevron)
// {
// 	int	fd;

// 	fd = -1;
// 	if (chevron->type == OUT)
// 		fd = open(chevron->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	else if (chevron->type == DOUBLE_OUT)
// 		fd = open(chevron->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	if (fd < 0)
// 		perror("open_file error");
// 	return (fd);
// }

// void	handle_in_redirection(t_chevron *current, int *fd_in)
// {
// 	if (*fd_in != -1)
// 		close(*fd_in);
// 	*fd_in = open_file_in(current);
// 	if (*fd_in == -1)
// 		return ;
// 	dup2(*fd_in, STDIN_FILENO);
// }

// void	handle_out_redirection(t_chevron *current, int *fd_out)
// {
// 	if (*fd_out != -1)
// 		close(*fd_out);
// 	*fd_out = open_file_out(current);
// 	if (*fd_out == -1)
// 		return ;
// 	dup2(*fd_out, STDOUT_FILENO);
// }

int open_redirection_file(const char *filename, int flags, mode_t mode)
{
	int fd = open(filename, flags, mode);
	if (fd == -1)
	{
		perror("open");
		return -1;
	}
	return fd;
}

void apply_redirection(int fd, int std_fd)
{
	if (dup2(fd, std_fd) == -1)
	{
		perror("dup2");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void handle_all_heredocs(t_token *token)
{
    t_token *current_token = token;
    t_chevron *current_chevron;
    int heredoc_fd;
    char *line;

    while (current_token)
    {
        current_chevron = current_token->file_in_out;
        while (current_chevron)
        {
            if (current_chevron->chevron_check && current_chevron->type == DOUBLE_IN)
            {
                heredoc_fd = open_redirection_file("/tmp/heredoc_temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (heredoc_fd == -1)
                    exit(EXIT_FAILURE);

                printf("Starting heredoc, waiting for delimiter: %s\n", current_chevron->next->value);
                while ((line = readline("> ")) != NULL)
                {
                    if (strcmp(line, current_chevron->next->value) == 0)
                    {
                        free(line);
                        break;
                    }
                    write(heredoc_fd, line, strlen(line));
                    write(heredoc_fd, "\n", 1);
                    free(line);
                }
                close(heredoc_fd);
                printf("Heredoc file closed after writing\n");

                // Vérifiez si le fichier heredoc_temp existe
                if (access("/tmp/heredoc_temp", F_OK) != -1)
                {
                    printf("heredoc_temp file exists\n");

                    // Imprimez le contenu du fichier après l'écriture
                    FILE *f = fopen("/tmp/heredoc_temp", "r");
                    if (f)
                    {
                        char c;
                        printf("Content of /tmp/heredoc_temp:\n");
                        while ((c = fgetc(f)) != EOF)
                            putchar(c);
                        fclose(f);
                    }
                    else
                    {
                        perror("fopen heredoc_temp after writing");
                    }
                }
                else
                {
                    printf("heredoc_temp file does not exist\n");
                }
            }
            current_chevron = current_chevron->next;
        }
        current_token = current_token->next;
    }
}

void handle_redirections(t_token *token)
{
    t_chevron *current = token->file_in_out;
    int fd;

    while (current)
    {
        if (current->chevron_check)
        {
            if (current->type == OUT)
            {
                fd = open_redirection_file(current->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd != -1)
                    apply_redirection(fd, STDOUT_FILENO);
            }
            else if (current->type == DOUBLE_OUT)
            {
                fd = open_redirection_file(current->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (fd != -1)
                    apply_redirection(fd, STDOUT_FILENO);
            }
            else if (current->type == IN)
            {
                fd = open_redirection_file(current->next->value, O_RDONLY, 0644);
                if (fd != -1)
                    apply_redirection(fd, STDIN_FILENO);
            }
            else if (current->type == DOUBLE_IN)
            {
                fd = open("/tmp/heredoc_temp", O_RDONLY);
                if (fd == -1) {
                    perror("open heredoc");
                } else {
                    printf("Redirecting stdin from /tmp/heredoc_temp\n");
                    printf("File descriptor for heredoc_temp: %d\n", fd);

                    // Vérifiez l'état du descripteur avant dup2
                    if (fcntl(fd, F_GETFD) == -1)
                    {
                        perror("fcntl check failed");
                        close(fd);
                        exit(EXIT_FAILURE);
                    }

                    if (dup2(fd, STDIN_FILENO) == -1) {
                        perror("dup2");
                        close(fd);
                        exit(EXIT_FAILURE);
                    }
                    printf("Redirection to stdin successful\n");
                    close(fd);
                }
            }
        }
        current = current->next;
    }
}

void remove_heredoc_chevrons(t_token *token)
{
    t_chevron *prev = NULL;
    t_chevron *current = token->file_in_out;

    while (current)
    {
        if (current->chevron_check && current->type == DOUBLE_IN)
        {
            t_chevron *to_free = current;
            if (prev)
                prev->next = current->next->next;
            else
                token->file_in_out = current->next->next;

            current = current->next->next;

            free(to_free->next->value);
            free(to_free->next);
            free(to_free->value);
            free(to_free);
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }

    if (token->value)
    {
        char *start = strstr(token->value, "<<");
        if (start)
        {
            char *end = strstr(start, " end");
            if (end)
                memmove(start, end + 4, strlen(end + 4) + 1);
        }
    }
}
