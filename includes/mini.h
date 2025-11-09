/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:15:37 by alejandj          #+#    #+#             */
/*   Updated: 2025/11/09 01:12:26 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

// Colors
#define RED   "\033[0;31m"
#define GREEN "\033[0;32m"
#define BLUE  "\033[0;34m"
#define RESET "\033[0m"

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

typedef struct s_mini
{
	char	**env;
	char	*line;
	char	*prompt;
	char	**cmd;
	char	**arr_path;
	pid_t	simple_cmd_process;
	int		last_status;
}			t_mini;

typedef struct s_env
{
	char	*var;
	char	*value;
}			t_env;

// Obtain vars env
char	*get_home(char **env);
char    *get_prompt(char **env);
char	**get_path_cmd(char **env);

// Built-ins
int		ft_echo(t_mini *mini);
int		ft_cd(t_mini *mini);
int		ft_pwd(void);
void	ft_export(t_mini *mini);
void	ft_env(char **env);

// Export utils
int		get_num_vars_env(char **env);
int		get_len_var(char *str);

// Execution
void	execute_simple_commands(t_mini *mini);

// Print errors
void	print_cmd_error(char *cmd, char *error);

#endif