/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:45:09 by alejandj          #+#    #+#             */
/*   Updated: 2025/11/22 21:35:40 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static void	has_quotes(char *s, int *in_word, int *count, int *i)
{
	char	quote;

	if (!*in_word)
	{
		*in_word = 1;
		(*count)++;
	}
	quote = s[(*i)++];
	while (s[*i] && (s[*i] != quote))
		(*i)++;
	if (s[*i] == quote)
		(*i)++;
}

static int	count_tokens(char *s)
{
	int		i;
	int		in_word;
	int		count;

	in_word = 0;
	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			has_quotes(s, &in_word, &count, &i);
			continue ;
		}
		if (s[i] == ' ')
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		i++;
	}
	return (count);
}

static char	*build_word(char *str, int *i)
{
	char	buffer[4096];
	int		j;
	char	quote;

	j = 0;
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n'))
		(*i)++;
	while (str[*i] && (str[*i] != ' ' && str[*i] != '\t' && str[*i] != '\n'))
	{
		if (str[*i] == '\'' || str[*i] == '\"')
		{
			quote = str[*i];
			(*i)++;
			while (str[*i] && (str[*i] != quote))
				buffer[j++] = str[(*i)++];
			if (str[*i] == quote)
				(*i)++;
		}
		else
			buffer[j++] = str[(*i)++];
	}
	buffer[j] = '\0';
	return (ft_strdup(buffer));
}

char	**split_tokens(char *str)
{
	char	**arr;
	int		n_tokens;
	int		index;
	int		i;

	n_tokens = count_tokens(str);
	arr = malloc((n_tokens + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	index = 0;
	while (index < n_tokens)
	{
		arr[index] = build_word(str, &i);
		index++;
	}
	arr[index] = NULL;
	return (arr);
}
