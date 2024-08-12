/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:43:41 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/12 15:20:41 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BUFFER_SIZE 1024

# ifdef __linux__
#  include <linux/limits.h>
# elif defined(__APPLE__)
#  include <sys/syslimits.h>
# endif

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
# include <readline/history.h>
# include <readline/readline.h>
// # include <term.h>
# include <limits.h>
// # include <linux/limits.h>
# include <stdbool.h>
# include "../include/utils/libft/libft.h"
# include "../include/utils/ft_printf/includes/ft_printf.h"
# include "../include/utils/gnl/get_next_line.h"

typedef enum s_token_type
{
    TOKEN_COMMAND,
    TOKEN_PIPE
}   t_token_type;

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
t_token 		*main_parsing(char *input);
int    			process_token(char *token, t_token **token_list);
void    		finalize_parsing(t_token **new_node, char **tokenarray);
//01
char			**ft_split_quoted(const char *str);
//02
t_token			*create_command_node(char *input);
t_token			*create_pipe_node(void);
void			add_token_node(t_token **head, t_token *new_node);
//03
bool			is_builtin_command(char *com);
bool			check_builtin(char *value);
char			*get_builtin_info(char *value);
char			*close_quotes_if_needed(char *str);
char			*clean_whitespace(char *str);
//10
void			print_token_list(t_token *head);
void			free_token_list(t_token *token_list);
void			free_token_array(char **tokenarray);

//--------------------------------------------------------------------------//
//									Expension								//
//20
//void			expanser_commands(t_token token_list);
char			*get_env_value(const char *name, t_envfinal *env);
char			*expand_variables_in_value(const char *value, t_envfinal *env); 
void			process_token_values(t_token *token, t_envfinal *env);
//21
bool			is_relativ_path(const char *path);
char			*get_absolute_path(const char *relative_path);
void			clean_path(char *path);
//22
char 			*resolve_path(const char *path); 
//23
char			*join_path(const char *path, const char *cmd);
char			*get_command_path(const char *cmd);

//--------------------------------------------------------------------------//
//									Execution								//
//00
void			main_exec(t_token *token, t_envfinal *env);
void			main_command(t_token *token, t_envfinal *env);
void			other_command(t_token *token, t_envfinal *env);
//01
// void			execute_execve(t_token *token, char **tokenarray,
// 					char **envarray);
void			execute_execve(t_token *token, t_envfinal *env);
//02
char			**convert_env(t_envfinal *env);
char			**free_env(char **str, int count);
int				count_env(t_envfinal *env);
//03
char			**convert_token(t_token *token);
char			**free_token(char **str, int count);
int				count_token(t_token *token);
//10
void			handle_sigint(int sig);
//20
void 			execute_pipes(t_token *token, t_envfinal *env);
//30
void			launch_minishell(char **env);
//31
void 			exe_clear(void);


//--------------------------------------------------------------------------//
//									Builtin									//
//00
char *get_env_value2(const char *var, t_envfinal *env);
void update_env(t_envfinal *env, char *var, char *value);
char *get_target_path2(t_token *token, t_envfinal *env);
void exe_cd(t_token *token, t_envfinal *env);

//01
int				exe_echo(char *str);
//02
void			mini_env(t_envfinal *envp);
//03
void			exe_export(t_envfinal *env, t_token *token);
//04
void			exe_unset(t_envfinal **env, t_token *token);
//05
int				exe_pwd(void);
//06
void			exe_exit(char *str, t_envfinal *env, t_token *token);
//10
int				builtin_check(t_token *token);
void			builtin_selector(t_token *token, t_envfinal *env);
//20
int				check_word_count(char **cmd_list);
int				get_env_len(char *line);
int				is_proper_env(char *env_name);
//--------------------------------------------------------------------------//
//									Environement							//
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








// Debut de test

// fin de tes



#endif
