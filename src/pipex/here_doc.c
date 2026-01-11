/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:46:39 by aleconst          #+#    #+#             */
/*   Updated: 2026/01/08 20:49:40 by alejandj         ###   ########.fr       */
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
		write(2, "\nminishell: warning: here-document at line ", 43);
		ft_putnbr_fd(n_line, 2);
		write(2, " delimited by end-of-file (wanted «", 36);
		write(2, delimiter, ft_strlen(delimiter));
		write(2, "»)\n", 4);
	}
}

int	here_doc(t_mini *mini, char *delimiter, int type_quote)
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
		if (type_quote == NO_QUOTES)
			line = expand_line(mini, line);
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
		n_line++;
		ft_printf("> ");
		line = get_next_line(STDIN_FILENO);
	}
	manage_line(delimiter, line, n_line);
	return (close(pipe_fd[1]), pipe_fd[0]);
}
