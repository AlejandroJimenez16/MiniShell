/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:15:37 by alejandj          #+#    #+#             */
/*   Updated: 2025/11/03 14:35:00 by alejandj         ###   ########.fr       */
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
}			t_mini;

// Obtain vars env
char	*get_home(char **env);
char    *get_prompt(char **env);
char	**get_path_cmd(char **env);

// Builtins
int		ft_cd(t_mini *mini);

#endif