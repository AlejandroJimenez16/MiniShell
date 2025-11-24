/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:15:37 by alejandj          #+#    #+#             */
/*   Updated: 2025/11/24 12:35:36 by alejandj         ###   ########.fr       */
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
# include "pipex_bonus.h"
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

// Main structure
typedef struct s_mini
{
	char	**env;
	char	*line;
	char	*prompt;
	char	**cmd;
	char	**arr_path;
	pid_t	simple_cmd_process;
	int		exit_code;
}			t_mini;

// Environment structure
typedef struct s_env
{
	char	*var;
	char	*value;
	char	*full;
}			t_env;

// Info tokens structure
typedef enum e_quote_type
{
    NO_QUOTES,
    SINGLE_QUOTES,
    DOUBLE_QUOTES
} t_quote_type;

typedef struct	s_token_info
{
	t_quote_type	type_quote;
}					t_token_info;

// Obtain vars env
char	*get_home(char **env);
char	*get_prompt(char **env);
char	**get_path_cmd(char **env);

// Built-ins
int		is_builtin(char **cmd);
void	exec_builtins(t_mini *mini);
void	ft_echo(char **cmd);
int		ft_cd(t_mini *mini);
void	ft_pwd(t_mini *mini);
void	ft_export(t_mini *mini);
void	ft_unset(t_mini *mini);
void	ft_env(char **env);
void	ft_exit(t_mini *mini);

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
char	**split_tokens(char *str, t_token_info **t_info);
void	expand_vars(t_mini *mini, t_token_info *t_info);

// Execution
void	child_simple_cmd(t_mini *mini);

// Print errors
void	print_cmd_error(char *cmd, char *error);

#endif