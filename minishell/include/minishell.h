/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:43:41 by acabarba          #+#    #+#             */
/*   Updated: 2024/09/24 17:36:34 by acabarba         ###   ########.fr       */
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

/**
 * Variable global pour la gestion du PID et du code erreur (echo $?)
 */
//int			exit_val;
//extern int g_status_cmd;
/* Variable global devoir yo.

*/

extern pid_t	g_status_cmd;
/**
 * Enum pour les liste chainé.
 */
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
	DOUBLE_OUT,
	COMMAND
}	t_chevron_type;

/**
 * Liste chainé pour l'execution
 */
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

typedef struct s_chevron
{
	t_chevron_type		type;
	char				*value;
	struct s_chevron	*next;
}	t_chevron;

/**
 * Stucture d'environement.
 */
typedef struct s_envp
{
	char	**env;
}	t_envp;

/**
 * Stucture pour les signaux.
 */
typedef struct s_signal
{
	int	sigint;
	int	sigquit;
	int	sigterm;
}	t_signal;

/**
 * Creation de structure pour la norme
 */
typedef struct s_chevron_data
{
	char			**current_position;
	t_chevron		**head;
	t_chevron		**last_command_node;
	char			*chevron;
	int				token_length;
	int				token_index;
	t_chevron_type	*types;
}	t_chevron_data;

typedef struct s_exp_data
{
	size_t	i;
	size_t	j;
	int		in_single_quotes;
	int		in_double_quotes;
	size_t	len;
	char	*result;
}	t_exp_data;

typedef struct s_process_data
{
	t_token		*token;
	t_envp		*envp;
	t_signal	*handler;
	int			in;
	int			out;
}	t_process_data;

//--------------------------------------------------------------------------//
//									Parsing									//
//00
t_token			*main_parsing(char *input, t_envp *env);
int				parse_tokens(char **tokenarray, t_token **token_list);
int				process_single_token(char *token, t_token **token_list);
int				add_pipe_to_list(t_token **token_list);
int				process_token(char *token, t_token **token_list);
//01
char			*extract_token(const char *str, int start, int len);
int				handle_quote(char c, bool *in_quotes, char *quote_char);
char			**process_split(const char *str, char **result, int *count);
char			**ft_split_quoted(const char *str);
bool			is_pipe_in_q(const char *input, int index);

//02
t_token			*create_command_node(char *input);
t_token			*create_pipe_node(void);
void			add_token_node(t_token **head, t_token *new_node);
//03
bool			is_builtin_command(char *com);
bool			check_builtin(char *value);
char			*get_builtin_info(char *value);
void			check_quotes(const char *str, bool *s_q_open, bool *d_q_open);
char			*close_quotes_if_needed(char *str);
char			*clean_whitespace(char *str);
void			finalize_parsing(t_token *new_node, char **tokenarray);
int				check_onlyspace(char *str);
//10
void			print_token_list(t_token *head);
void			free_token_list(t_token *token_list);
void			free_token_array(char **tokenarray);
void			free_tokens(char **tokens);
void			free_chevron_list(t_chevron *chevron_list);
//11
char			*join_path(const char *path, const char *cmd);
void			free_paths(char **paths);
char			*try_access_command(char **paths, const char *cmd);
char			*get_command_path(const char *cmd, t_envp *envp);
char			*ft_getenv(t_envp *envp, const char *path);


//--------------------------------------------------------------------------//
//									Expension								//
//20
char			*extract_var_name_env(const char *value, size_t *i);
void			append_env_value_env(t_exp_data *data,
					const char *env_value);
char			*expand_variables_in_value(const char *value, char **env);
char			*clean_string(const char *str);
void			process_token_values(t_token *token, char **env);
void			insert_string_into_result(t_exp_data *data, const char *str);
//21
t_exp_data		*init_expansion_data(const char *value);
void			free_expansion_data(t_exp_data *data);
//30
t_chevron		*create_chevron(t_chevron_type type, const char *value);
void			append_chevron(t_chevron **head, t_chevron_type type,
					const char *value);
void			print_chevron_list(t_chevron *head);
void			main_parse_string_chevron(t_token *token);
//31
t_chevron		*parse_string_chevron(char *str);
void			parse_chevron_token(char **current_position, t_chevron **head,
					t_chevron **last_command_node);
void			initialize_tokens_types(char **tokens, t_chevron_type *types);
//32
void			find_chevron_in_str(char *current_position, char **tokens,
					t_chevron_data *data);
void			parse_before_chevron(t_chevron_data *data);
void			parse_after_chevron(t_chevron_data *data);
//33
char			*get_chevron_type_str(t_chevron_type type);
void			print_chevron_node(t_token *token);
int				contains_chevrons(const char *str);

//--------------------------------------------------------------------------//
//									Execution								//
//00
void			main_exec(t_token *token, t_envp *envp, t_signal *handler);
void			main_command(t_token *token, t_envp *envp, t_signal *handler);
void			main_command_chevron(t_token *token, t_envp *envp,
					t_signal *handler);
//01
void			handle_memory_error(char **split_args, char **args);
void			execute_child_process(char *cmd_path,
					char **split_args, t_envp *envp);
int				prepare_command(char ***split_args, char ***args,
					t_token *token);
int				prepare_execution(char **split_args,
					char **args, char **cmd_path, t_envp *envp);
void			execute_execve(t_token *token, t_envp *envp, t_signal *handler);
//02
int				count_tokens(const char *str, char delimiter);
char			*allocate_token(const char *start, size_t len);
char			*get_next_token(const char **str, char delimiter);
void			free_split_command(char **args);
char			**split_command(const char *cmd);
//03
void			cleanup_execution(char **split_args,
					char **args, char *cmd_path);
void			file_descriptor_handler(int in, int out);
void			handle_parent_process(pid_t pid, t_signal *handler);
void			handle_child_process(t_process_data *args);
void			create_child_process(t_process_data *args);
//04
char			**free_token(char **str, int count);
int				count_token(t_token *token);
int				count_tokens_before_pipe(t_token *token);
char			**allocate_and_fill_tokens(t_token *token, int count);
char			**convert_token(t_token *token);
//10
void			handle_signals_in_parent(t_signal *handler);
void			signal_handler(int sig, siginfo_t *info, void *context);
void			init_signal_handlers(t_signal *handler);
pid_t			fork_and_execute(char *cmd_path,
					char **split_args, t_envp *envp);
//20
void			create_and_handle(t_process_data *args,
					int *fd_in, int *pipefd);
void			execute_pipes(t_token *token, t_envp *envp, t_signal *handler);
//21
void			setup_process_args(t_process_data *args,
					int fd_in, int *pipefd);
void			setup_redirections(int fd_in, int fd_out);
void			create_pipe_if_needed(int *pipefd, t_token *token);
void			handle_pipe_child_process(t_process_data *args, int *pipefd);
void			handle_pipe_parent_process(pid_t pid, int *fd_in, int *pipefd);
//30
int				open_infile(char *filename);
int				open_outfile(char *filename, int flags);
int				redirect_infile(char *filename);
int				redirect_outfile(char *filename, int append);
void			handle_redirections(t_chevron *chevron_list);
//31
void			handle_heredoc_input(int pipefd[2], char *delimiter);
void			handle_heredoc(char *delimiter);

//--------------------------------------------------------------------------//
//									Builtin									//
//00
int				exe_cd(char *input, t_envp *envp);
//01
int				exe_echo(char *str);
void			ft_fflush_stdout(void);
//02
void			mini_env(t_envp *envp);
//03.1
char			*create_env_entry(const char *var, const char *value);
int				get_env_size(char **env);
char			**allocate_env_array(char **old_env,
					int old_size, int new_size);
void			add_env_variable(t_envp *envp, char *new_entry);
void			exe_export(t_envp *envp, char *args);
//03.2
void			set_env_var(t_envp *envp, const char *var, const char *value);
void			update_env(t_envp *envp, const char *var, int var_len,
					char *new_entry);
int				is_var_in_env(t_envp *envp, const char *var);
void			process_export_token(t_envp *envp, char *token);
//03.3
void			insertion_sort(char **array, int size);
char			**copy_env(char **env, int size);
void			print_sorted_env(char **env);
//04
// void			exe_unset(t_envp *envp, char *var);
// void			unset_variable(t_envp *envp, const char *var);
// void			shift_env_vars(char **env, int start);
char	**copy_env_without_var(char **env, const char *var);
void	exe_unset(t_envp *envp, char *args);
void	free_env(char **env);
//05
int				string_to_int(const char *str, int *result);
int				exe_pwd(void);
//06
int				string_to_int(const char *str, int *result);
void			exe_exit(char *str, t_envp *envp, t_token *token);
//10
int				builtin_check(t_token *token);
void			builtin_selector(t_token *token, t_envp *envp);
void			builtin_selector_chevron(t_token *token, t_envp *envp);
//20
int				check_word_count(char **cmd_list);
int				get_env_len(char *line);
int				is_proper_env(char *env_name);
int				error_flag(void);
int				skip_spaces(const char *str, int index);
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
