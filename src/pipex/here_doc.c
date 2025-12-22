/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_heredoc_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleconst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:46:39 by aleconst          #+#    #+#             */
/*   Updated: 2025/06/13 13:46:41 by aleconst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static void	manage_line(char *delimiter, char *line, int n_line)
{
	if (line)
		free(line);
	else
	{
		write(2, "\nwarning: here-document at line ", 32);
		ft_putnbr_fd(n_line, 2);
		write(2, " delimited by end-of-file (wanted «", 36);
		write(2, delimiter, ft_strlen(delimiter));
		write(2, "»)\n", 4);
	}
}

int	here_doc(char *delimiter)
{
	int		pipe_fd[2];
	int		n_line;
	char	*line;

	if (pipe(pipe_fd) == -1)
		return (-1);
	n_line = 1;
	ft_printf("> ");
	line = get_next_line(STDIN_FILENO);
	while (line && !(ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& ((ft_strlen(line) == ft_strlen(delimiter)
					&& line[ft_strlen(line) - 1] != '\n')
				|| (ft_strlen(line) - 1 == ft_strlen(delimiter)
					&& line[ft_strlen(line) - 1] == '\n'))))
	{
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
		n_line++;
		ft_printf("> ");
		line = get_next_line(STDIN_FILENO);
	}
	manage_line(delimiter, line, n_line);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}
