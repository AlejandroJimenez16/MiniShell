/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 20:28:23 by alejandj          #+#    #+#             */
/*   Updated: 2025/12/17 20:49:51 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static int	handle_operators(char *str, int *i)
{
	int	count;

	count = 1;
	if ((str[*i] == '<' && str[*i + 1] == '<')
		|| (str[*i] == '>' && str[*i + 1] == '>'))
		(*i) += 2;
	else
		(*i)++;
	return (count);
}

static int	handle_normal_word(char *str, int *i)
{
	char	quote;
	int		count;

	count = 1;
	while (str[*i] && (str[*i] != ' ' && str[*i] != '\t'
			&& str[*i] != '|' && str[*i] != '<' && str[*i] != '>'))
	{
		if (str[*i] == '\'' || str[*i] == '"')
		{
			quote = str[(*i)++];
			while (str[*i] && (str[*i] != quote))
				(*i)++;
			if (str[*i] == quote)
				(*i)++;
		}
		else
			(*i)++;
	}
	return (count);
}

int	count_tokens(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		if (!str[i])
			break ;
		if (str[i] == '|' || str[i] == '<' || str[i] == '>')
			count += handle_operators(str, &i);
		else
			count += handle_normal_word(str, &i);
	}
	return (count);
}
