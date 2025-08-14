/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 22:52:25 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/13 23:42:12 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>

# define SUCCESS 0
# define FAILURE 1
# define STDERR_FILENO 2

// Global variable for exit status
extern int				g_last_exit_code;

// Token types
enum					e_token_type
{
	SPACES = 1,
	WORD,
	VAR,
	PIPE,
	INPUT,
	TRUNC,
	HEREDOC,
	APPEND,
	END
};

// Token status
enum					e_status
{
	DEFAULT = 1, //s_Def
	SQUOTE, //s_SQ
	DQUOTE, //s_DQ
};

typedef struct s_proc_ctx
{
    char	*new_str;
    char	*oldstr;
    char	*var_value;
    int		index;
    int		*i;
    int		*j;
}	t_proc_ctx;

typedef struct s_io_fds
{
	char	*infile;
	char	*outfile;
	char	*heredoc_delimiter;
	bool	heredoc_quotes;
	int		fd_in;
	int		fd_out;
	int		stdin_backup;
	int		stdout_backup;
}	t_io_fds;

typedef struct s_command
{
	char				*command;
	char				*path;
	char				**args;
	bool				pipe_output;
	int					*pipe_fd;
	t_io_fds			*io_fds;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

typedef struct s_token
{
	char				*str;
	char				*str_backup;
	bool				var_exists;
	int					type;
	int					status;
	bool				join;
	struct s_token		*prev;
	struct s_token		*next;
}						t_token;

typedef struct s_data
{
	bool				interactive;
	t_token				*token;
	char				*user_input;
	char				**env;
	char				*working_dir;
	char				*old_working_dir;
	t_command			*cmd;
	pid_t				pid;
}						t_data;

// Libft functions
int						ft_strcmp(const char *s1, const char *s2);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
size_t					ft_strlen(const char *s);
char					*ft_strdup(char *src);
char					*ft_strjoin(const char *s1, const char *s2);
char					*ft_substr(const char *s, unsigned int start,
							size_t len);
void					*ft_calloc(size_t count, size_t size);
void					*ft_memset(void *b, int c, size_t len);
char					*ft_itoa(int n);
void					ft_putendl_fd(char *s, int fd);
char					*ft_strchr(const char *s, int c);
char					**ft_split(char const *s, char c);
char					*join_back(char **tab);

// Memory management
void					free_ptr(void *ptr);
void					free_iteration_data(t_data *data);
void					free_data(t_data *data);
void					free_str_tab(char **tab);
void					init_inf_outf(t_command *command);

// Parsing functions
bool					parsing(t_data *data);
int						first_step(t_data *data);
bool					second_step(t_data *data);
void					third_step(t_data *data);
bool					is_all_space(char *str);
int						tokenizer(t_data *data);
int						save_token(int *i, char *str, int start, t_data *data);
int						put_flag(int flag, char *str, int i);
int						process_type(int *i, char *str, int start,
							t_data *data, int type);
int						parse_quotes(t_data *data);
int						then_remove_quotes(t_token **token);
void					copy_new_line(t_token **token, char *new_line);

// Token functions
t_token					*create_token(char *str, char *str_backup, int type,
							int status);
void					add_token_to_list(t_token **list, t_token *new_node);
int						token_word(t_token **token_list, char *str, int index,
							int start);
int						token_separator(t_token **lst, char *str, int i,
							int type);
void					delete_token(t_token *lst);
void					clear_list_token(t_token **lst);

// Variable checking and syntax validation
int						var_or_consecutive(t_token **token_lst);
int						check_consecutives(t_token **token_lst);

// Expansion functions
int						expansion(t_data *data, t_token **token_lst);
char					*expansion_heredoc(t_data *data, char *str);
char					*get_var_value(t_token *token, char *str, t_data *data);
char					*get_var_name(char *str);
char					*extract_var_env(t_data *data, char *var);
void					remove_char_at_index(char **str, int index);
bool					var_inside_quotes(char *str, int i);
bool					valid_var_start(char c);
bool					is_special_var(char c);
bool					check_next_sep(char c);
void					update_status(t_token **node, char c);

// Variable expansion utilities
char					*replace_var(t_token **token, char *str, char *var,
							int i);
char					*replace_var_heredoc(char *str, char *var_value,
							int index);
int						expand_var(t_token **token, char *var, int i);
int						delete_var(t_token **token_node, char *token_str,
							int i);
void					copy_var_value(char *new_str, char *var_value, int *j);
char					*new_token_string(char *oldstr, char *var_value,
							int newstr_size, int index);

// Variable name utilities
bool					valid_name(char c);
int						count_var_chars(char *str, int start);
int						find_dollar_pos(char *str);
int						var_end(char *str);

// Error handling
void					error_msg(char *errmsg, char *detail, int quotes);
int						error_cmd(char *command, char *detail, char *error_message, int error_nb);
char					*append_str(char *base, char *addition);

// Builtin functions (to be implemented)
void					exit_builtin(t_data *data, char **args);
void					handle_quotes(t_data *data);
void					create_commands(t_data *data);
t_command				*cmd_list_append(t_command **cmd, bool flag);

// Command handling functions
void					handle_heredoc(t_command **cmd, t_token **tokens,
							t_data *data);
void					handle_pipe(t_command **cmd, t_token **tokens);
void					handle_input_redirection(t_command **cmd,
							t_token **tokens);
void					handle_trunc_redirection(t_command **cmd,
							t_token **tokens);
void					handle_append(t_command **cmd, t_token **tokens);
void					handle_word_var(t_command **cmd, t_token **token_lst);
void					commands_with_no_args(t_data *data);

// Command argument handling
int						fill_arguments(t_token **token, t_command *cmd);
int						create_args_def(t_token **tok, t_command *l_cmd);
int						add_args_def(t_token **tok, t_command *l_cmd);
int						create_args_echo(t_token **token_node,
							t_command *last_cmd);
int						add_args_echo(t_token **tok, t_command *cmd);
int						count_arguments(t_token *temp);
void					create_args_from_split(char **split, t_token **new_tok);
void					split_token(t_command *last_cmd, char *cmd_str);
void					remove_empty_args(t_token **tokens);
void					copy_existing_args(char **new_tab, char **args,
							int len);
char					*join_vars(t_token **token_node);

// Heredoc functions
bool					write_to_heredoc(t_data *data, t_io_fds *io, int fd);
bool					parse_heredoc_line(t_data *data, char **line,
							t_io_fds *io, bool *ret);
bool					handle_eof_line(t_io_fds *io, bool *ret);
bool					is_delimiter_match(char *line, t_io_fds *io, bool *ret);
bool					handle_var_expansion(t_data *data, char **line,
							t_io_fds *io, bool *ret);
char					*read_heredoc_line(void);
void					write_heredoc_line(char *line, int fd);
char					*split_expand_join(t_data *data, char *line);

// I/O functions
bool					remove_old_infile(t_io_fds *io);

// Initialization and utility functions
void					set_to_zero(void *ptr, size_t size);
void					check_arguments(t_data *data, int ac, char **av);
bool					init_data(t_data *data, char **env);
bool					init_working_dirs(t_data *data);

#endif