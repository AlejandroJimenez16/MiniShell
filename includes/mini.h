/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:15:37 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/13 14:08:44 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

// Colors
# define RED   "\033[0;31m"
# define GREEN "\033[0;32m"
# define BLUE  "\033[0;34m"
# define RESET "\033[0m"

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <termcap.h>
# include <errno.h>

extern int	g_sig_status;

// Main structure
typedef struct s_mini
{
	char	**env;
	char	*line;
	char	*prompt;
	char	**arr_path;
	int		exit_code;
	char	*last_command;
	int		has_env;
}			t_mini;

// Environment structure
typedef struct s_env
{
	char	*var;
	char	*value;
	char	*full;
}			t_env;

// Cmd structure
typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC
}	t_token_type;

// Info tokens structure
typedef enum e_quote_type
{
	NO_QUOTES,
	SINGLE_QUOTES,
	DOUBLE_QUOTES
}	t_quote_type;

// List of redirections for s_cmd
// @param type number from e_token_type (REDIR_IN, REDIR_OUT...)
// @param file name of the file or the delimiter
// @param qyotes type of quote
typedef struct s_redir
{
	int		type;
	char	*file;
	int		quote;
}	t_redir;

typedef struct s_cmd
{
	char			**cmd;
	int				cmd_index;
	t_quote_type	*cmd_quotes;
	int				cmd_size;
	t_list			*redirs;
}			t_cmd;

typedef struct s_token_info
{
	t_quote_type	type_quote;
	t_token_type	type_token;
}					t_token_info;

typedef struct s_pipex
{
	int		pipefd[2];
	int		prev_pipe_in;
	int		fd_in;
	int		fd_out;
	pid_t	pid;
}			t_pipex;

typedef struct s_fill_cmds
{
	char			**new_cmd;
	t_quote_type	*new_cmd_quotes;
	int				new_i;
}					t_fill_cmds;

// Obtain prompt
char	*get_prompt(int has_env, char **env);

// Env utils
char	*get_env(char *var, char **env);
void	set_env(t_mini *mini, char *var, char *value);
size_t	get_len_var(char *str);
char	**get_path_cmd(char **env);
char	**copy_env(char **env);
void	sort_env(char **cpy_env);

// Built-ins
int		is_env_builtin(char **cmd);
int		is_builtin(char **cmd);
int		exec_env_builtins_parent(t_cmd *node, t_mini *mini, t_pipex *pipex);
void	exec_env_builtins(char **cmd, t_mini *mini);
int		exec_builtins(char **cmd, t_mini *mini);
void	ft_echo(char **cmd);
int		ft_cd(char **cmd, t_mini *mini);
void	ft_pwd(t_mini *mini);
void	ft_export(char **cmd, t_mini *mini);
void	ft_unset(char **cmd, t_mini *mini);
void	ft_env(char **env);
void	ft_exit(char **cmd, t_mini *mini);

// Parser
int		count_tokens(char *s);
void	set_token_type(char *token, t_token_info *t_info);
void	set_quote_type(char quote, t_token_info *t_info);
char	**split_tokens(char *str, t_token_info **t_info);
int		check_unclosed_quotes(char *line);
int		check_invalid_tokens(t_token_info *t_info, t_mini *mini,
			char **invalid, int *is_bonus);
char	*remove_quotes(char *value, int len_value);

// Expand vars
int		handle_exit_code_copy(t_mini *mini, char *result, int *i);
int		handle_last_command_copy(t_mini *mini, char *result, int *i);
int		handle_env_var_copy(t_mini *mini, char *arg, int *i, char *result);
int		get_len_expand_var(char *str);
char	*get_env_value(char *env_entry);
int		get_len_token(t_mini *mini, char *arg);
char	*expand_vars_in_token(t_mini *mini, char *arg);
// Word splitting
int		has_separators(char *tokens);
int		word_splitting(t_cmd *node, char *result, int i);

void	expand_vars(t_cmd *node, t_mini *mini);

// Create cmd list
t_cmd	*init_node(int n_words);
void	add_redir_to_node(t_cmd *node, int prev_token,
			char *token, t_quote_type type_quote);
void	assign_token_to_node(t_cmd *node, char *token,
			t_token_info *t_info, int *i);
int		get_prev_token(t_token_info *t_info, int i);
t_list	*create_cmd_list(char *line, char **tokens, t_token_info *t_info);

// Redirections
int		handle_redirections(t_cmd *node, t_pipex *pipex, t_mini *mini);

// Execution
int		wait_for_children(pid_t last_pid);
void	execute_simple_commands(char **cmd, t_mini *mini);
void	execute_commands(t_list *cmd_list, t_mini *mini);

// Pipex utils
void	init_pipex(t_pipex *pipex);
int		create_pipe(t_pipex *pipex, t_mini *mini);

// Mini utils
void	print_cmd_error(char *cmd, char *error);
void	print_unexpected_error(t_mini *mini, int is_bonus, char *invalid);
int		get_cmd_arr_size(char **tokens, t_token_info *t_info, int start);
int		get_num_nodes(char *line, t_token_info *t_info);
int		is_redir(int type);

// Signals
void	init_signals(void);
void	setup_child_signals(void);

// Heredoc
int		here_doc(t_mini *mini, char *delimiter, int type_quote);

// Frees
void	*ft_free_wa(char **word_arr);
void	free_redir(void *content);
void	free_cmd_node(void *context);
void	free_mini(t_mini *mini);

#endif
