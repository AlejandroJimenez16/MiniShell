/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleconst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:05:39 by aleconst          #+#    #+#             */
/*   Updated: 2025/05/20 12:05:44 by aleconst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <wait.h>
# include "../libft/libft.h"

# define ERROR_MALLOC "Error: Memory full"

typedef struct s_context
{
	int		argc;
	char	**argv;
	char	**env;
	int		io[2];
	int		order;
	int		cmd_order;
	int		pipe_io[2];
	int		pipe2_io[2];
	int		mode;
}	t_context;

int		pipex(int argc, char **argv, char **env, int mode);
void	stderror_manager(char *message, int has_prerror, int exit_mode);
void	create_path(char **s1, char *s2);
void	redirect_io(t_context *context);
int		get_last_status(pid_t last_pid, int argc, char **argv);
int		is_empty_cmd(const char *cmd);
void	error_str(int has_error, char *cmd);
void	redirect_pipe(t_context *context);
void	sync_pipes(t_context *context);
int		here_doc(char *delimiter);
void	close_all(t_context *context);
void	manage_line(char *delimiter, char *line, int n_line);
void	*ft_free_wa(char **word_arr);

//Parser for integration with minishell
int		detect_mode(char *line);
char	**extract_commands(char *line);
char	*extract_outfile(char *line);
char	*extract_word_after(char *line, char *key);
int		count_items(char **cmds);
char	**parse_line(char *line);
int		execute_pipex(int argc, char **argv, char **env);
int		get_limit(int argc, int mode);
void	continue_redirect_io(t_context *context);

#endif
