/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:43:41 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/14 21:38:30 by yonieva          ###   ########.fr       */
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
# include <readline/history.h>
# include <readline/readline.h>
# include <term.h>
# include <limits.h>
# include <linux/limits.h>
# include <stdbool.h>
# include "../include/utils/libft/libft.h"
# include "../include/utils/ft_printf/includes/ft_printf.h"
# include "../include/utils/gnl/get_next_line.h"

typedef enum s_token_type
{
	TOKEN_COMMAND,
	TOKEN_PIPE
}		t_token_type;

typedef enum s_chevron_type
{
	IN,
	DOUBLE_IN,
	OUT,
	DOUBLE_OUT
}	t_chevron_type;

typedef struct s_chevron
{
	t_chevron_type	type;
	bool	is_last_open;
	bool	is_last_closed;
	char	*file_name;
	struct s_chevron	*next;
}	t_chevron;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	bool				is_builtin;
	char				*builtin_info;
	bool				is_last_command;
	struct s_chevron	*file_in_out;
	struct s_token		*next;
}	t_token;

typedef struct s_envp
{
	char	**env;
}	t_envp;

//--------------------------------------------------------------------------//
//									Parsing									//
//00
t_token			*main_parsing(char *input, t_envp *env);
int				parse_tokens(char **tokenarray, t_token **token_list);
int				process_single_token(char *token, t_token **token_list);
int				add_pipe_to_list(t_token **token_list);
int				process_token(char *token, t_token **token_list);
void			finalize_parsing(t_token *new_node, char **tokenarray);

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
void			free_tokens(char **tokens);
//11
char			*join_path(const char *path, const char *cmd);
char			*get_command_path(const char *cmd);

//--------------------------------------------------------------------------//
//									Expension								//
//20
void			process_token_values(t_token *token, char **env);
void			parse_chevrons(t_token *tokens);
char 			*clean_string(const char* str);

//--------------------------------------------------------------------------//
//									Execution								//
//00
void			main_exec(t_token *token, t_envp *envp);
void			main_command(t_token *token, t_envp *envp);
//01
void			execute_execve(t_token *token, t_envp *envp);
//02
char			**split_command(const char *cmd);
//03
char			**convert_token(t_token *token);
int				count_token(t_token *token);
//10
void			handle_sigint(int sig);
//20
void			execute_pipes(t_token *token, t_envp *env);
char			**free_token(char **str, int count);

//--------------------------------------------------------------------------//
//									Builtin									//
//00
int				exe_cd(char *input, t_envp *envp);
//01
int				exe_echo(char *str);
//02
void			mini_env(t_envp *envp);
//03
char			*create_env_entry(const char *var, const char *value);
void			add_env_variable(t_envp *envp, char *new_entry);
void			set_env_var(t_envp *envp, const char *var, const char *value);
void			update_env(t_envp *envp, const char *var, int var_len,
					char *new_entry);
void			process_export_token(t_envp *envp, char *token);
void			exe_export(t_envp *envp, char *args);
//04
void			unset_variable(t_envp *envp, const char *var);
void			exe_unset(t_envp *envp, char *var);
//05
int				exe_pwd(void);
//06
void			exe_exit(char *str, t_envp *envp, t_token *token);

//10
int				builtin_check(t_token *token);
void			builtin_selector(t_token *token, t_envp *envp);
//20
int				check_word_count(char **cmd_list);
int				get_env_len(char *line);
int				is_proper_env(char *env_name);
//--------------------------------------------------------------------------//
//									Environement							//
//00
void			edit_shlvl(char **env);
void			init_terminal(t_envp *envp);
int				count_env_vars(char **env);
char			**duplicate_env(char **env, int var_env);
t_envp			env_dup(char **env);
//10
void			print_env(char **env);
char			*get_env_value(char *str, char **env);
void			set_env_value(char **env, char *key, char *new_value);
void			free_array(char **array);
void			free_t_envp(t_envp *envp);

#endif
