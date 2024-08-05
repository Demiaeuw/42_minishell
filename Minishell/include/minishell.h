/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:43:41 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/06 01:06:23 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BUFFER_SIZE 1024

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <sys/wait.h>
# include <unistd.h>
# include <term.h>
# include <limits.h>
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
typedef enum s_token_type
{
	TOKEN_COMMAND,
	TOKEN_ARGUMENT,
	TOKEN_PIPE,
	TOKEN_REDIRECTION,
	TOKEN_STRING,
	TOKEN_VARIABLE,
	TOKEN_UNKNOWN
}	t_token_type;

/**
 * macros pour la gestion d erreur des builtins
 */
typedef enum e_builtin_error
{
	MANY_ARG,
	INVALID_ARG
}	t_builtin_error;

//---------------------------------------------------------------------------//
/**
 * Liste chainé des tokens.
 * Permet d'enregistrer une suite logique de Token.
 */
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	bool			is_builtin;
	char			*builtin_info;
	bool			is_last_command;
	struct s_token	*next;
}	t_token;

//---------------------------------------------------------------------------//
/**
 * Niveau du Shell
 */
typedef struct s_shell
{
	int				level;
}	t_shell_level;
//---------------------------------------------------------------------------//
// Parsing
//00
void			main_error(void (*f)(), int index);
void			ft_error(int index);
//01
t_token			*create_token(t_token_type type, char *value);
void			add_token(t_token **token_list, t_token *new_token);
void			*safe_malloc(size_t bytes);
t_shell_level	*init_shlvl(void);
//02
void			free_token_value(void *value);
void			free_token_list(t_token **lst, void (*del)(void*));
void			free_split_result(char **result);
void			free_shlvl(t_shell_level *shlvl);
//03
char			*get_token_type_name(t_token_type type);
void			print_tokens(t_token *token);
void			signature(void);
//10
t_token			*main_parse(char *str);
char			**step01(char *str);
t_token			*step02(char **array);
//11
t_token_type	token_compare(char *arg);
void			last_command(t_token *token);
//12
t_token			*simplify_list(t_token *token);
//13
void			copy_com(const char *src, char *dest);
bool			is_builtin_command(char *com);
void			add_builtin(t_token *token);
//20
void			expanser_commands(t_token token_list);
//21
bool			is_relativ_path(const char *path);
char			*get_absolute_path(const char *relative_path);
void			clean_path(char *path);
//22
char			*extend_result(char *result, size_t size, size_t add_size);
char			*append_var(char *res, const char *var, t_envlist *envp_list, size_t size);
char			*process_var(const char *start, const char **end,
								char *res, size_t size,
								char **res_ptr, t_list *envp_list);
//---------------------------------------------------------------------------//
// Execution
//10
void			display_prompt(void);
char			*read_input(void);

//---------------------------------------------------------------------------//
//builtin
//00
int				exe_cd(char *str, t_envlist *envp_list);
//01
int				exe_echo(char *str, t_envlist *envp_list);
//02
int				mini_env(char	**str, t_envlist *envp_list);
//03
int				mini_export(char **str, t_envlist *envp_list);
//04
void			print_export(t_envlist *envplist);
//05
int				exe_pwd(char *str, t_envlist *envp_list);
//06
void			mini_exit(char *str, t_envlist *envp_list, t_shell_level *shell);
//07
void    		exe_exit(char *str, t_list *envp_list, t_shell_level *shell);
//10
int				check_word_count(char **cmd_list);
int				get_env_len(char *line);
int				is_proper_env(char *env_name);
void			gestion_erreur_bt(char *cmd, char *word, int status);

#endif
