/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:43:41 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/08 19:53:15 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BUFFER_SIZE 1024

#ifdef __linux__
#include <linux/limits.h>
#elif defined(__APPLE__)
#include <sys/syslimits.h>
#endif

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
//# include <linux/limits.h>
# include <stdbool.h>
# include "../include/utils/libft/libft.h"
# include "../include/utils/ft_printf/includes/ft_printf.h"
# include "../include/utils/gnl/get_next_line.h"

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

typedef enum e_builtin_error
{
	MANY_ARG,
	INVALID_ARG
}	t_builtin_error;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	bool			is_builtin;
	char			*builtin_info;
	bool			is_last_command;
	struct s_token	*next;
}	t_token;

typedef struct s_envfinal
{
	char				*type;
	char				*content;
	struct s_envfinal	*next;
}	t_envfinal;
//--------------------------------------------------------------------------//
//									Parsing									//
//00
void			main_error(void (*f)(int), int index);
void			ft_error(int index);
//01
t_token			*create_token(t_token_type type, char *value);
void			add_token(t_token **token_list, t_token *new_token);
void			*safe_malloc(size_t bytes);
//02
void			free_token_value(void *value);
void			free_token_list(t_token **lst, void (*del)(void*));
void			free_split_result(char **result);
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
void			add_combined_token(t_token **simplst, char **combival,
					bool *firstcmd);
void			add_pipe_token(t_token **simplified_list);
void			combine_value(char **combival, char *current_value,
					bool *firstcmd);
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
// char			*extend_result(char *result, size_t size, size_t add_size);
// char			*append_var(char *res, const char *var, t_env *envp_list,
//					size_t size);
// char			*process_var(const char *start, const char **end,
// 					char *res, size_t size, char **res_ptr, t_list *envp_list);
//--------------------------------------------------------------------------//
//									Execution								//
//01
// void			main_init_envp(t_env *envp_list, char **envp);
//10
void			display_prompt(void);
char			*read_input(void);

//--------------------------------------------------------------------------//
//									builtin									//
//00
// int				exe_cd(char *str, t_env *envp_list);
//01
int				exe_echo(char *str);
//02
void			mini_env(t_envfinal *envp);
//03
// int				mini_export(char **str, t_env *envp_list);
// void			print_export(t_env *envplist);
//04
int				mini_unset(t_token *token, t_envfinal *env);

//05
int				exe_pwd(void);
//06
void			exe_exit(char *str, t_envfinal *env, t_token *token);
//10
void			main_builtin(t_token *token, t_envfinal *env);
int				builtin_check(t_token *token);
void			builtin_selector(t_token *token, t_envfinal *env);
void			execute_execve(t_token *token);
//20
int				check_word_count(char **cmd_list);
int				get_env_len(char *line);
int				is_proper_env(char *env_name);
void			gestion_erreur_bt(char *cmd, char *word, int status);

//--------------------------------------------------------------------------//
//									envp									//
//00
void			main_env(t_envfinal **env, char **envp);
t_envfinal		*create_env_node(const char *type, const char *content);
void			add_env_node(t_envfinal **env_list, t_envfinal *new_node);
void			init_env_list(t_envfinal **env_list, char **envp);
void			print_env_list(t_envfinal *env_list);
void			increment_shlvl(t_envfinal *env);
void			decrement_shlvl(t_envfinal *env);
//01
void			free_node(t_envfinal *node);
void			free_env_list(t_envfinal *env_list);
//02
void			increment_int(t_envfinal *env, char *str);
void			decrement_int(t_envfinal *env, char *str);
void			modif_env(t_envfinal *env, char *type_env, char *new_content);
char			*find_envcontent(t_envfinal *env, char *type_env);


#endif
