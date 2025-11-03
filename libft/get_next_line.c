/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:23:31 by alejandj          #+#    #+#             */
/*   Updated: 2025/03/10 14:21:41 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (size > 0)
	{
		i = 0;
		while (src[i] != '\0' && i < size)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

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
	if (bytes_read == -1)
	{
		free(*line);
		*line = NULL;
		return (0);
	}
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
	static char	buffer[BUFFER_SIZE];
	char		*line;
	char		*temp;

	if (fd < 0)
		return (NULL);
	line = ft_strdup("");
	if (line == NULL)
		return (NULL);
	while (1)
	{
		if (*buffer == '\0')
		{
			if (buffer_is_empty(fd, buffer, &line) == 0)
				return (line);
		}
		if (ft_strchr(buffer, '\n'))
			return (n_in_buffer(buffer, line));
		temp = ft_strjoin(line, buffer);
		if (!temp)
			return (free(line), NULL);
		free(line);
		line = temp;
		ft_memset(buffer, '\0', BUFFER_SIZE);
	}
}
