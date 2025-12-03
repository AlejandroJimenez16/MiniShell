/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:45:09 by alejandj          #+#    #+#             */
/*   Updated: 2025/12/03 20:17:10 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static	char	*build_word(char *str, int *i, t_token_info *t_info)
{
	char	buffer[1024];
	int		j;
	char	quote;

	t_info->type_quote = NO_QUOTES;
	j = 0;
	
	// Saltar espacios
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
	if (!str[*i])
		return (NULL);
	
	// Comillas
	if (str[*i] == '\'' || str[*i] == '"')
	{
		quote = str[*i];
		set_quote_type(quote, t_info);
		(*i)++;
		while (str[*i] && (str[*i] != quote))
			buffer[j++] = str[(*i)++];
		if (str[*i] == quote)
			(*i)++;
		buffer[j] = '\0';
        return ft_strdup(buffer);
	}
	// Redirecciones y Pipes
	else if (str[*i] == '|')
	{
		buffer[0] = str[*i];
		buffer[1] = '\0';
		(*i)++;
		return (ft_strdup(buffer));
	}
	else if (str[*i] == '<' || str[*i] == '>')
	{
		if ((str[*i] == '<' && str[*i + 1] == '<') || (str[*i] == '>' && str[*i + 1] == '>'))
		{
			buffer[0] = str[*i];
			buffer[1] = str[*i + 1];
			buffer[2] = '\0';
			(*i) += 2;
			return (ft_strdup(buffer));
		}
		buffer[0] = str[*i];
		buffer[1] = '\0';
		(*i)++;
		return (ft_strdup(buffer));
	}
	else
	{
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
		arr[index] = build_word(str, &i, &(*t_info)[index]);
		set_token_type(arr[index], &(*t_info)[index]);
		index++;
	}
	arr[index] = NULL;
	return (arr);
}
