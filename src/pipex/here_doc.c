/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:46:39 by aleconst          #+#    #+#             */
/*   Updated: 2026/02/02 16:48:24 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static char	*expand_line(t_mini *mini, char *line)
{
	char	*temp;

	temp = line;
	line = expand_vars_in_token(mini, line);
	free(temp);
	return (line);
}

static void	manage_line(char *delimiter, char *line, int n_line)
{
	if (line)
		free(line);
	else
	{
		write(1, "\n", 1);
		write(2, "minishell: warning: here-document at line ", 42);
		ft_putnbr_fd(n_line, 2);
		write(2, " delimited by end-of-file (wanted «", 36);
		write(2, delimiter, ft_strlen(delimiter));
		write(2, "»)\n", 4);
	}
}

void	read_heredoc_loop(t_mini *mini, t_heredoc *hd)
{
	hd->n_line = 1;
	write(1, "> ", 2);
	hd->line = get_next_line(STDIN_FILENO);
	while (hd->line && g_sig_status == 0)
	{
		if ((ft_strncmp(hd->line, hd->delimiter, ft_strlen(hd->delimiter)) == 0
				&& ((ft_strlen(hd->line) == ft_strlen(hd->delimiter)
						&& hd->line[ft_strlen(hd->line) - 1] != '\n')
					|| (ft_strlen(hd->line) - 1 == ft_strlen(hd->delimiter)
						&& hd->line[ft_strlen(hd->line) - 1] == '\n'))))
		{
			break ;
		}
		if (hd->type_quote == NO_QUOTES)
			hd->line = expand_line(mini, hd->line);
		write(hd->pipe_fd[1], hd->line, ft_strlen(hd->line));
		free(hd->line);
		hd->n_line++;
		write(1, "> ", 2);
		hd->line = get_next_line(STDIN_FILENO);
	}
}

int	here_doc(t_mini *mini, char *delimiter, int type_quote)
{
	t_heredoc	hd;

	hd.delimiter = delimiter;
	hd.type_quote = type_quote;
	if (pipe(hd.pipe_fd) == -1)
		return (-1);
	hd.stdin_backup = dup(STDIN_FILENO);
	signal(SIGINT, heredoc_sigint_handler);
	read_heredoc_loop(mini, &hd);
	if (g_sig_status != 0)
	{
		dup2(hd.stdin_backup, STDIN_FILENO);
		close(hd.stdin_backup);
		if (hd.line)
			free(hd.line);
		return (close(hd.pipe_fd[0]), close(hd.pipe_fd[1]), -1);
	}
	close(hd.stdin_backup);
	setup_child_signals();
	manage_line(hd.delimiter, hd.line, hd.n_line);
	return (close(hd.pipe_fd[1]), hd.pipe_fd[0]);
}
