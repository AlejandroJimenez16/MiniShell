/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:39:26 by alejandj          #+#    #+#             */
/*   Updated: 2025/03/10 14:40:21 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*add_char(char *s, char c)
{
	int		i;
	int		size;
	char	*new_word;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	new_word = (char *)malloc(size + 2);
	if (!new_word)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		new_word[i] = s[i];
		i++;
	}
	new_word[i] = c;
	new_word[i + 1] = '\0';
	return (new_word);
}

static int	buffer_is_empty(int fd, char *buffer, char **line)
{
	ssize_t	bytes_read;
	char	*temp;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read >= 0)
		buffer[bytes_read] = '\0';
	if (bytes_read == -1)
		return (free(*line), *line = NULL, 0);
	if (bytes_read == 0)
	{
		if (*line && **line != '\0')
		{
			temp = add_char(*line, '\0');
			if (!temp)
				return (free(*line), *line = NULL, 0);
			return (free(*line), *line = temp, 0);
		}
		return (free(*line), *line = NULL, 0);
	}
	return (1);
}

static char	*n_in_buffer(char *buffer, char *line)
{
	char	*after_n;
	int		i;
	char	*temp;

	if (!ft_strchr(buffer, '\n'))
		return (NULL);
	after_n = ft_strdup(ft_strchr(buffer, '\n') + 1);
	if (!after_n)
		return (NULL);
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
	{
		temp = add_char(line, buffer[i]);
		free(line);
		line = temp;
		i++;
	}
	if (buffer[i] == '\n')
	{
		temp = add_char(line, buffer[i]);
		return (free(line), line = temp, ft_memset(buffer, '\0', BUFFER_SIZE),
			ft_strlcpy(buffer, after_n, ft_strlen(after_n)), free(after_n),
			line);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;
	char		*temp;

	if (fd < 0)
		return (NULL);
	if (!buffer[fd])
	{
		buffer[fd] = malloc(BUFFER_SIZE + 1);
		if (!buffer[fd])
			return (NULL);
		buffer[fd][0] = '\0';
	}
	line = ft_strdup("");
	while (1)
	{
		if (*buffer[fd] == '\0' && buffer_is_empty(fd, buffer[fd], &line) == 0)
			return (free(buffer[fd]), buffer[fd] = NULL, line);
		if (ft_strchr(buffer[fd], '\n'))
			return (n_in_buffer(buffer[fd], line));
		temp = ft_strjoin(line, buffer[fd]);
		free(line);
		line = temp;
		ft_memset(buffer[fd], '\0', BUFFER_SIZE);
	}
}
