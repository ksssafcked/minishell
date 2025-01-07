/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 17:33:54 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/03 17:08:43 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../dprintf/ft_printf.h"
# include "get_next_line.h"
# include <ctype.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define TOKEN_UNQUOTED 'U'
# define TOKEN_SINGLE_QUOTE 'S'
# define TOKEN_DOUBLE_QUOTE 'D'

typedef struct s_shell
{
	struct s_env		*env;
	char				*directory;
	int					last_exit_code;
	int					should_exit;
}						t_shell;

typedef struct s_env
{
	char				*var;
	struct s_env		*next;
	int					printable;
}						t_env;

typedef struct s_command
{
	char				**argv;
	char				*infile;
	char				*outfile;
	int					append;
	char				*heredoc_delim;
	int					in_fd;
	int					out_fd;
	int					heredoc_quoted;
	struct s_command	*next;
}						t_command;

typedef struct s_pipeline
{
	t_command	*commands;
}						t_pipeline;

typedef struct s_parser_context
{
	const char	**line_ptr;
	char		*token;
	int			in_single_quote;
	int			in_double_quote;
	size_t		capacity;
	size_t		length;
}						t_parser_context;

typedef struct s_process_vars
{
	char				*line;
	char				**tokens;
	t_pipeline			*pl;
	int					status;
}						t_process_vars;

typedef struct s_exec_context
{
	t_command			*cmd;
	int					idx;
	int					cmd_count;
	int					(*pipes)[2];
	t_env				*env;
	t_shell				*shell;
}						t_exec_context;

typedef struct s_exec_params
{
	t_env				*env;
	t_shell				*shell;
}						t_exec_params;

typedef struct s_exec_context_params
{
	t_command			*cmd;
	int					idx;
	int					cmd_count;
	int					(*pipes)[2];
	t_exec_params		*params;
}						t_exec_context_params;

typedef struct s_expand_context
{
	t_env				*env;
	int					last_exit_code;
}						t_expand_context;

typedef struct s_expand_con
{
	int					last_exit_code;
	int					*i;
	t_env				*env;
}						t_expand_con;

typedef struct s_indices
{
	int					left;
	int					right;
	size_t				i;
	size_t				j;
}						t_indices;

typedef struct s_heredoc_info
{
	int					h_q;
	char				*delim;
	t_expand_context	*context;
	int					line_count;
	int					delim_found;
}						t_heredoc_info;

typedef struct s_quote_state
{
	int					in_single_quote;
	int					in_double_quote;
}						t_quote_state;

char					*ft_substr_custom(const char *s, unsigned int start);
t_env					*get_env_var(t_env *env, char *env_name);
int						count_args(char **args);
void					change_pwd(t_env *env, char *directory);
int						change_dir(t_shell *shell, char *directory, char *arg);
int						cd_cmd(t_shell *shell, t_env *env, char **args);
int						is_numeric_argument(char *arg);
void					free_env_and_exit(t_env *env, int code);
void					print_numeric_error(char *arg, t_env *env);
void					print_too_many_args_error(void);
int						exit_cmd(char **args, int last_exit_code,
							int *should_exit, t_env *env);
void					env_cmd(t_env *env);
int						is_nl_arg(char *args);
void					pwd_cmd(t_shell *shell);
char					*parse_new_dir(t_shell *shell, char **args);
char					*parse_dir(char *dir);
char					*delete_last_dir(char *directory, int index);
char					*delete_this_dir(char *dir, int index, int len);
char					*add_direct(const char *s1, const char *s2);
int						get_len(const char *s1, const char *s2);
void					echo_cmd(char **args);
int						cmp_strings(const void *a, const void *b);
void					print_env_variable(const char *env_var);
void					free_array(char **arr, int size);
void					sort_and_print(char **arr, int size);
void					print_export(t_env *env);
void					set_env_var(t_env *env, const char *new_var);
void					set_env_no_value(t_env *env, const char *new_var);
int						is_valid_identifier(const char *var);
size_t					has_value(char *str);
bool					process_argument(t_env *env, char *arg, int *exit_code);
void					export_cmd(t_shell *shell, t_env *env, char **args);
int						is_matching_var(const char *var, const char *var_name);
void					free_env_node(t_env *node);
t_env					*delete_node(t_env *prev, t_env *cur, t_env *env);
t_env					*remove_env_var(t_env *env, const char *var_name);
t_env					*unset_cmd(t_env *env, char **args);
int						handle_echo(t_shell *shell, char **args);
int						handle_cd(t_shell *shell, char **args);
int						handle_pwd(t_shell *shell, char **args);
int						handle_export(t_shell *shell, char **args);
int						handle_unset(t_shell *shell, char **args);
int						handle_env(t_shell *shell, char **args);
int						handle_exit(t_shell *shell, char **args);
int						run_builtin(t_shell *shell, char **args);
int						open_all_redirections(t_pipeline *pl, int *exit_code);
/// env.c

t_env					*get_env_var(t_env *env, char *env_name);
t_env					*env_add_var(t_env *env, const char *new_var);
char					*env_get_value(t_env *env, const char *name);
char					**env_to_char_array(t_env *env);
int						env_size(t_env *env);
void					env_print(t_env *env);
t_env					*env_new_elem(char *var);
t_env					*env_init(char **envp);
void					env_free(t_env *env);

extern int				g_cmd_error_code;
extern sig_atomic_t		g_received_signal;

void					set_error_and_code(const char *cmd, const char *msg,
							int code);
int						count_colons(const char *env_path);
char					**split_path(const char *env_path);
int						is_valid_path(const char *full, struct stat *st,
							const char *cmd);
char					*handle_path(const char *cmd);
char					*handle_missing_command(const char *cmd);
char					*construct_full_path(const char *dir, const char *cmd);
char					*get_command_path(t_env *env, const char *cmd);
void					free_dirs(char **dirs);
char					**allocate_dirs(int count);
char					*allocate_and_copy_dir(const char *env_path, int start,
							int end);
int						populate_dirs(const char *env_path, char **dirs,
							int count);
char					*search_directories(char **dirs, const char *cmd,
							struct stat *st);
int						is_builtin_cmd(char **argv);
int						count_commands(t_command *cmd);
void					close_pipes(int cmd_count, int (*pipes)[2]);
int						setup_pipes(int cmd_count, int (*pipes)[2]);
void					handle_error_file(const char *cmd);
int						open_input_file(t_command *cmd);
int						dup_input_fd(int fd);
int						setup_input_redirection(t_command *cmd);
int						configure_output_flags(t_command *cmd, int *flags);
int						open_output_file(t_command *cmd, int flags);
int						dup_output_fd(int fd);
int						setup_output_redirection(t_command *cmd);
int						setup_redirections(t_command *cmd);
char					*get_command_path_or_exit(t_env *env, char *cmd);
char					**prepare_envp(t_env *env);
void					execute_builtin(t_shell *shell, char **argv);
void					execute_external(t_env *env, char **argv, char *pat,
							char **e_ex);
int						duplicate_fds(t_exec_context *ctx);
void					close_all_pipes(t_exec_context *ctx);
void					execute_command(t_exec_context *ctx);
void					child_process(t_exec_context *ctx);
pid_t					fork_and_execute(t_exec_context *ctx);
void					wait_for_children(int cmd_count, pid_t *pids,
							int *last_exit_code);
int						initialize_pipes(int cmd_count, int (**pipes)[2]);
t_exec_context			init_exec_context(t_exec_context_params *ctx_params);
pid_t					e(t_exec_context_params *ctx_params);
pid_t					*c(int c_c, t_command *cmd, int (*pipes)[2],
							t_exec_params *par);
void					init_exec_params(t_exec_params *params, t_env *env,
							t_shell *shell);
int						handle_pids_error(int cmd_count, int (*pipes)[2]);
int						close_pipes_and_wait(int cmd_count, int (*pipes)[2],
							pid_t *pids);
int						execute_pipeline(t_pipeline *pipeline, t_env *env,
							t_shell *shell);
int						process_redirections_step(t_pipeline *pl, t_shell *s,
							char *line);
char					*expand_token(const char *token, t_env *env,
							int last_exit_code);
int						is_heredoc_quoted(const char *delim);
char					*remove_quotes(const char *str);
int						w_to_p(int fd, const char *line, int h_q,
							t_expand_context *c);
int						c_heredoc_pipe(char *delim, int h_q,
							t_expand_context *context);
int						handle_single_heredoc(t_command *cmd,
							t_expand_context *context);
int						process_heredocs(t_command *cmds, t_env *env,
							int last_exit_code);
int						handle_heredoc_loop(int fd_write, t_heredoc_info *info);
void					i(t_heredoc_info *i, char *d, int h_q,
							t_expand_context *c);
void					free_pipeline(t_pipeline *pl);
int						process_builtins_step(t_pipeline *pl,
							t_shell *shell, char *line);
int						init_pipe(int *fd);
char					**ft_split_line(char *line);
int						c_heredoc_pipe_core(int fd_write, t_heredoc_info *info);
char					*delete_quote(char *line);
int						is_double_quote(const char *str);
int						is_simple_quote(const char *str);
char					**process_tokens(const char *ptr, char **tokens,
							size_t count);
int						add_token(char ***tokens, size_t *count, char *token);
char					**cleanup_tokens(char **tokens, size_t count);
char					*get_next_token(const char **line);
char					*pl(t_parser_context *ctx);
int						handle_quotes(char c, t_parser_context *ctx);
char					*resize_token(char *token, size_t *capacity);
char					*allocate_initial_token(size_t capacity);
void					skip_spaces(const char **line);
char					*preprocess_line(const char *line);
int						preprocess_loop(const char *line, char *new_line,
							size_t len);
char					*allocate_new_line(size_t len);
int						handle_char(const char *line, char *new_line, size_t i,
							size_t *j);
void					update_quote_states(char c, int *in_sq, int *in_dq);
size_t					h_spe_char(const char *l, char *n_l, size_t i,
							size_t *j);
void					hand_t_s(const char *line, char *new_line, size_t i,
							size_t *j);
int						is_double_operator(const char *line, size_t i);
void					add_special_char(char *new_line, char c, size_t *j);
void					add_space_if_needed(char *new_line, size_t *j);
int						is_special_char(char c);
int						is_whitespace(char c);
int						is_quote(char c);
int						is_escaped(const char *line, size_t i);
int						is_operator_token(char *s);
int						sep(char c);
int						is_pipe(char *line);
int						is_double_redirection(char *line);
int						is_single_redirection(char *line);
char					*get_clean(char *line, size_t size);
char					*get_spaces(char *line);
int						parse_pipeline(char **tokens, t_pipeline **pip);
int						pst(t_pipeline *pipe, t_command **cmd, char **tokens,
							int *index);
int						hstok(t_command **cmd, char *token, int *index,
							char **tokens);
int						open_and_close_file(const char *filename, int append);
int						open_and_close_infile(const char *filename);
int						set_heredoc(t_command *cmd, char *token);
int						set_output_file(t_command *cmd, char *token,
							int append);
int						set_input_file(t_command *cmd, char *token);
t_command				*create_new_command(t_pipeline *pipeline);
void					append_command_to_pipeline(t_pipeline *pipeline,
							t_command *cmd);
int						extend_arguments(t_command *cmd, char *token);
char					**extend_argv(char **argv, int count);
t_command				*allocate_command(void);

void					init_signals(void);
void					reset_signals(void);

int						ft_strcmp(char *s1, char *s2);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
size_t					ft_strlen(const char *str);
char					*ft_strdup(const char *src);
void					*ft_memcpy(void *dest_str, const void *src_str,
							size_t n);
char					*ft_strchr(const char *str, int c);
void					*ft_realloc(void *ptr, size_t size);
void					*ft_memset(void *str, int c, size_t n);
char					*ft_strnstr(const char *big, const char *little,
							unsigned int len);
int						ft_isalnum(int c);
void					*ft_calloc(size_t num, size_t size);
char					*ft_strcat(char *dest, const char *src);
char					*ft_strcpy(char *dest, const char *src);
int						ft_isdigit(int d);
char					**ft_split(char const *str, char c);
char					*ft_strjoin(const char *s1, const char *s2);
char					*ft_strncpy(char *dest, const char *src,
							unsigned int n);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
long					ft_strtol(const char *str, char **endptr, int base);
void					ft_qsort(void *base, size_t nmemb, size_t size,
							int (*cmp)(const void *, const void *));

int						handle_ctrl_backslash(int count, int key);
int						is_operator_token(char *s);
int						is_single_command_no_pipe(t_pipeline *pl);
int						validate_syntax(char **t, int count);
char					**copy_tokens(char **tokens, int start);
char					**get_next_pipe(char **tokens);
int						initialize_shell(t_shell *shell, char **envp);
char					*read_input_line(void);
char					**tokenize_line(char *line);
int						count_tokens(char **tokens);
int						check_syntax(char **t, int count, t_shell *shell);
void					expand_tokens_quotes(char **tokens, t_shell *shell,
							int idx);
void					remove_empty_tokens(char **tokens, int *idx);
void					expand_and_clean_tokens(char **tokens, t_shell *shell);
void					handle_parse_error(char **tokens, t_shell *shell);
char					**handle_par_return_neg_one(char **tokens,
							t_shell *shell);
int						handle_parse_result(int par_return, char **tokens,
							t_shell *shell);
t_pipeline				*parse_pipeline_loop(char **tokens, t_shell *shell);
int						handle_redirections(t_pipeline *pl, t_shell *shell,
							char *line);
int						save_fds(int *saved_stdin, int *saved_stdout);
int						redirect_fds(t_command *c);
int						restore_fds(int saved_stdin, int saved_stdout);
void					execute_builtin_command(t_shell *shell, char **argv);
void					cleanup(t_pipeline *pl, char *line);
int						handle_builtin(t_pipeline *pl, t_shell *shell,
							char *line);
void					execute_commands(t_pipeline *pl, t_shell *shell);
t_pipeline				*parse_pipeline_step(char **t, t_shell *s, char *line);
char					*read_input_and_exit(void);
int						process_redirections_step(t_pipeline *pl, t_shell *s,
							char *line);
int						process_builtins_step(t_pipeline *pl, t_shell *shell,
							char *line);
int						execute_commands_step(t_pipeline *pl, t_shell *shell,
							char *line);
int						process_iterations(t_shell *shell);
int						process_iteration(int fd_write, t_heredoc_info *info);
void					*free_all(char **tab);
void					free_tokens(char **tokens);
void					free_pipeline(t_pipeline *pl);
void					free_command(t_command *c);
void					free_argv(char **argv);
void					shell_loop(t_shell *shell);
char					**tokenize_input(char *line);
int						process_quoted(char c, char *new_line, t_indices *idx);
int						process_unquoted(const char *line, char *new_line,
							t_indices *idx);
int						handle_unquoted(const char *line, char *new_line,
							t_indices *idx);
char					*allocate_initial_token(size_t capacity);
char					*allocate_new_line(size_t len);
int						validate_tokens(char **tokens, t_shell *shell,
							char *line);
int						handle_input(t_command **cmd, int *index,
							char **tokens);
int						handle_heredoc(t_command **cmd, int *index,
							char **tokens);
int						extract_name_value(const char *env_var, char **name,
							char **value);
void					print_declare(const char *name, const char *value,
							int needs_quotes);
int						value_needs_quotes(const char *v);
void					print_too_many_args_error(void);
void					print_numeric_error(char *arg, t_env *env);
int						process_iteration(int fd_write, t_heredoc_info *info);
int						process_heredocs(t_command *cmds, t_env *env,
							int last_exit_code);
char					*expand_token(const char *token, t_env *env,
							int last_exit_code);
char					*handle_char_sec(char *result, const char *token,
							t_expand_con *context);
char					*handle_default(char *result, const char *token,
							t_expand_con *context);
char					*handle_dollar_case(char *result, const char *token,
							t_expand_con *context);
char					*handle_backslash(char *result, const char *token,
							t_expand_con *context);
char					*handle_backslash_other(char *result, const char *token,
							t_expand_con *context);
char					*handle_backslash_backslash(char *result,
							const char *token, t_expand_con *context);
char					*handle_backslash_dollar(char *result,
							const char *token, t_expand_con *context);
char					*process_dollar(char *res, const char *token,
							t_expand_con *con);
char					*handle_dollar(char *result);
char					*h_v(char *result, const char *token, t_env *env,
							t_expand_con *con);
char					*append_var_value(char *result, const char *var_value);
char					*get_varname(const char *token, int *i, int *len);
int						is_valid_var_char(char c);
char					*extract_varname(const char *token, int start, int len);
char					*handle_question_mark(char *result,
							t_expand_con *context);
char					*append_char(char *result, char c);
char					*str_append(const char *s1, const char *s2);
char					*replace_variable(const char *name, t_env *env);

#endif
