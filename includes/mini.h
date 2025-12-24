/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:15:37 by alejandj          #+#    #+#             */
/*   Updated: 2025/12/25 00:33:58 by alejandj         ###   ########.fr       */
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

typedef struct s_cmd
{
	char	**cmd;
	int		cmd_size;
	char	*infile;
	int		heredoc;
	char	*delimeter;
	char	*outfile;
	int		append;
	int		index_start_cmd;
}			t_cmd;

// Info tokens structure
typedef enum e_quote_type
{
	NO_QUOTES,
	SINGLE_QUOTES,
	DOUBLE_QUOTES
}	t_quote_type;

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

// Obtain vars env
char	*get_home(char **env);
char	*get_prompt(char **env);
char	**get_path_cmd(char **env);

// Built-ins
int		is_env_builtin(char **cmd);
int		is_builtin(char **cmd);
int		exec_env_builtins(char **cmd, t_mini *mini);
int		exec_builtins(char **cmd, t_mini *mini);
void	ft_echo(char **cmd);
int		ft_cd(char **cmd, t_mini *mini);
void	ft_pwd(t_mini *mini);
void	ft_export(char **cmd, t_mini *mini);
void	ft_unset(char **cmd, t_mini *mini);
void	ft_env(char **env);
void	ft_exit(char **cmd, t_mini *mini);

// Export utils
size_t	get_len_var(char *str);
void	print_full_env(char **env);
char	*manage_has_value(char *var_value, char *eq);
char	**dup_env(char **env, int *i);
// Export parse
int		parse_export(char *var_value);
char	*remove_quotes(char *value, int len_value);
char	*build_clean_var(char *var, char *value, int len_value);

// Parser
int		count_tokens(char *s);
void	set_token_type(char *token, t_token_info *t_info);
void	set_quote_type(char quote, t_token_info *t_info);
char	**split_tokens(char *str, t_token_info **t_info);
int		check_unclosed_quotes(char *line);
int		check_invalid_tokens(t_token_info *t_info, t_mini *mini);

// Expand vars
int		get_len_expand_var(char *str);
char	*get_env_value(char *env_entry);
int		get_len_token(t_mini *mini, char *arg);
void	expand_vars(char **cmd, t_mini *mini, t_token_info *t_info, int start);

// Create cmd list
t_list	*create_cmd_list(char *line, char **tokens, t_token_info *t_info);

// Redirections
int		redirect_in(t_cmd *node, t_mini *mini, t_pipex *pipex);
int		redirect_out(t_cmd *node, t_mini *mini, t_pipex *pipex);

// Execution
int		wait_for_children(pid_t last_pid);
void	execute_simple_commands(char **cmd, t_mini *mini);
void	execute_commands(t_list *cmd_list, t_mini *mini, t_token_info *t_info);

// Pipex utils
void	init_pipex(t_pipex *pipex);
int		create_pipe(t_pipex *pipex, t_mini *mini);

// Mini utils
void	print_cmd_error(char *cmd, char *error);
int		get_cmd_arr_size(char **tokens, t_token_info *t_info, int start);
int		get_num_nodes(char *line, t_token_info *t_info);
int		is_redir(int type);

// Signals
void	init_signals(void);
void	setup_child_signals(void);

// Heredoc
int		here_doc(char *delimiter);

//Utils
void	*ft_free_wa(char **word_arr);

#endif
