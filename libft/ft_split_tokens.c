/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:45:09 by alejandj          #+#    #+#             */
/*   Updated: 2025/11/17 19:00:13 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static void	manage_quotes(char *s, int *i, int *in_word, int *count)
{
	char	quote;

	(*count)++;
	quote = s[*i];
	(*i)++;
	while (s[*i] && (s[*i] != quote))
		(*i)++;
	if (s[*i] == quote)
	{
		*in_word = 1;
		(*i)++;
	}
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
		if (s[i] == ' ')
			in_word = 0;
		else if (s[i] == '\'' || s[i] == '\"')
		{
			manage_quotes(s, &i, &in_word, &count);
			continue ;
		}
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
	int		start;
	int		end;
	char	quote;

	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n'))
		(*i)++;
	if (str[*i] == '\'' || str[*i] == '\"')
	{
		quote = str[*i];
		(*i)++;
		start = *i;
		while (str[*i] && (str[*i] != quote))
			(*i)++;
		end = *i;
		(*i) += (str[*i] == quote);
	}
	else
	{
		start = *i;
		while (str[*i] && str[*i] != ' ' && str[*i] != '\t' && str[*i] != '\n'
			&& str[*i] != '\'' && str[*i] != '\"')
			(*i)++;
		end = *i;
	}
	return (ft_substr(str, start, end - start));
}

char	**ft_split_tokens(char *str)
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
