/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:43:41 by acabarba          #+#    #+#             */
/*   Updated: 2024/08/13 23:23:08 by gaesteve         ###   ########.fr       */
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

typedef struct s_envp
{
	char	**env;
}	t_envp;

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
//11
char			*join_path(const char *path, const char *cmd);
char			*get_command_path(const char *cmd);

//--------------------------------------------------------------------------//
//									Expension								//
//20
void			process_token_values(t_token *token, char **env);
char			*ft_remove_quotes(char *str);

//--------------------------------------------------------------------------//
//									Execution								//
//00
void			main_exec(t_token *token, t_envp *envp);
void			main_command(t_token *token, t_envp *envp);
//01
void	execute_execve(t_token *token, t_envp *envp);
//02
char			**split_command(const char *cmd);
//03
char			**convert_token(t_token *token);
char			**free_token(char **str, int count);
int				count_token(t_token *token);
//10
void			handle_sigint(int sig);
//20
void			execute_pipes(t_token *token, t_envp *env);

//--------------------------------------------------------------------------//
//									Builtin									//
//00
int 			exe_cd(char *input, t_envp *envp);

//01
int				exe_echo(char *str);
//02
void			mini_env(t_envp *envp);
//03


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
t_envp			env_dup(char **env);
//10
void			print_env(char **env);
void			set_env_value(char **env, char *key, char *new_value);
char			*get_env_value(char *str, char **env);
void			free_array(char **array);

#endif
