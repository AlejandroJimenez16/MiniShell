/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:45:09 by alejandj          #+#    #+#             */
/*   Updated: 2025/12/03 21:37:31 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static char	*handle_quotes(char *str, int *i, t_token_info *t_info)
{
	char	quote;
	int		j;
	char	buffer[1024];

	j = 0;
	quote = str[*i];
	set_quote_type(quote, t_info);
	(*i)++;
	while (str[*i] && (str[*i] != quote))
		buffer[j++] = str[(*i)++];
	if (str[*i] == quote)
		(*i)++;
	buffer[j] = '\0';
	return (ft_strdup(buffer));
}

static char	*handle_pipes(char *str, int *i)
{
	char	*token;

	token = malloc(2);
	if (!token)
		return (NULL);
	token[0] = str[*i];
	token[1] = '\0';
	(*i)++;
	return (token);
}

static char	*handle_operators(char *str, int *i)
{
	char	*token;

	if ((str[*i] == '<' && str[*i + 1] == '<')
		|| (str[*i] == '>' && str[*i + 1] == '>'))
	{
		token = malloc(3);
		if (!token)
			return (NULL);
		token[0] = str[*i];
		token[1] = str[*i + 1];
		token[2] = '\0';
		(*i) += 2;
		return (token);
	}
	token = malloc(2);
	if (!token)
		return (NULL);
	token[0] = str[*i];
	token[1] = '\0';
	(*i)++;
	return (token);
}

static	char	*build_token(char *str, int *i, t_token_info *t_info)
{
	char	buffer[1024];
	int		j;

	t_info->type_quote = NO_QUOTES;
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
	if (!str[*i])
		return (NULL);
	if (str[*i] == '\'' || str[*i] == '"')
		return (handle_quotes(str, i, t_info));
	else if (str[*i] == '|')
		return (handle_pipes(str, i));
	else if (str[*i] == '<' || str[*i] == '>')
		return (handle_operators(str, i));
	else
	{
		j = 0;
		while (str[*i] && str[*i] != ' ' && str[*i] != '\t'
			&& str[*i] != '|' && str[*i] != '<' && str[*i] != '>')
			buffer[j++] = str[(*i)++];
		buffer[j] = '\0';
		return (ft_strdup(buffer));
	}
}

char	**split_tokens(char *str, t_token_info **t_info)
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
		arr[index] = build_token(str, &i, &(*t_info)[index]);
		set_token_type(arr[index], &(*t_info)[index]);
		index++;
	}
	arr[index] = NULL;
	return (arr);
}
