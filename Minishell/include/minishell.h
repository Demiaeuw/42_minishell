/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:43:41 by acabarba          #+#    #+#             */
/*   Updated: 2024/07/29 12:34:59 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>    // malloc, free, exit, getenv
# include <stdio.h>     // printf
# include <unistd.h>    // write, access, read, close, fork, execve, dup, dup2, pipe, getcwd, chdir, isatty
# include <fcntl.h>     // open, O_* constants
# include <sys/types.h> // opendir, readdir, closedir, stat, lstat, fstat, wait, waitpid, wait3, wait4
# include <sys/stat.h>  // stat, lstat, fstat
# include <dirent.h>    // opendir, readdir, closedir
# include <string.h>    // strerror
# include <errno.h>     // perror
# include <signal.h>    // signal, sigaction, sigemptyset, sigaddset, kill
# include <sys/ioctl.h> // ioctl
# include <termios.h>   // tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <sys/wait.h>  // wait, waitpid, wait3, wait4
# include <unistd.h>    // ttyname, ttyslot
# include <term.h>      // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <limits.h>	// max et min
# include <linux/limits.h>
# include <stdbool.h>
# include "../include/utils/libft/libft.h"
# include "../include/utils/ft_printf/includes/ft_printf.h"
# include "../include/utils/gnl/get_next_line.h"
# include "../srcs/envp/envp.h"

/**
 * Définition d'une énumération pour les types de tokens
 * Permet d'augmenter la lisibilité du code
 *
 * TOKEN_COMMAND : Représente une commande (ex: "ls", "cd" etc...)
 * TOKEN_ARGUMENT : Représente un argument de commande (ex: "-l")
 * TOKEN_PIPE : Représente le caractère de pipe ('|')
 * TOKEN_REDIRECTION : Représente les redirections ('>', '<', '>>' , '<<')
 * TOKEN_STRING : Représente une chaîne de caractères entre guillemets
 * TOKEN_VARIABLE : Représente une variable d'environnement (ex: "$PATH")
 * TOKEN_UNKNOWN : Représente un type de token inconnu ou non défini
 */

typedef enum
{
	TOKEN_COMMAND,
	TOKEN_ARGUMENT,
	TOKEN_PIPE,
	TOKEN_REDIRECTION,
	TOKEN_STRING,
	TOKEN_VARIABLE,
	TOKEN_UNKNOWN
}	token_type;

/**
 * Liste chainé des tokens.
 * Permet d'enregistrer une suite logique de Token.
 */
typedef struct s_token
{
	token_type type;
	char	*value;
	bool	builtin;
	bool	is_last_command;
	struct s_token *next;
}	t_token;



// Parsing
//00
void	main_error(void (*f)(), int index);
void	ft_error(int index);
//01
t_token	*create_token(token_type type, char *value);
void	add_token(t_token **token_list, t_token *new_token);
void	*safe_malloc(size_t bytes);
//02
void	free_token_value(void *value);
void	free_token_list(t_token **lst, void (*del)(void*));
void	free_split_result(char **result);
//03
char	*get_token_type_name(token_type type);
void	print_tokens(t_token *token);
//10
t_token	*main_argument(int ac, char **av);
char	**step01(int ac, char **av);
t_token	*step02(char **array);
//11
token_type	token_compare(char *arg);
//12
t_token	*simplify_list(t_token *token);
//20
//21
char    *get_absolute_path(const char *relative_path);

// Execution
//05
int		exe_cd(int ac, char **av);
int		exe_echo(char **av);

#endif
