/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:58:25 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/15 17:09:29 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void	set_token_type(char *token, t_token_info *t_info)
{
	if (t_info->type_quote != NO_QUOTES)
	{
		t_info->type_token = WORD;
		return ;
	}
	if (ft_strncmp(token, "<<", 3) == 0)
		t_info->type_token = HEREDOC;
	else if (ft_strncmp(token, ">>", 3) == 0)
		t_info->type_token = REDIR_APPEND;
	else if (ft_strncmp(token, "<", 2) == 0)
		t_info->type_token = REDIR_IN;
	else if (ft_strncmp(token, ">", 2) == 0)
		t_info->type_token = REDIR_OUT;
	else if (ft_strncmp(token, "|", 2) == 0)
		t_info->type_token = PIPE;
	else
		t_info->type_token = WORD;
}

void	set_quote_type(char quote, t_token_info *t_info)
{
	if (quote == '\'')
		t_info->type_quote = SINGLE_QUOTES;
	else if (quote == '\"')
		t_info->type_quote = DOUBLE_QUOTES;
}

static int	count_inside_quotes(char *str, int *i)
{
	char	quote;
	int		count;

	count = 0;
	quote = str[(*i)++];
	while (str[*i] && (str[*i] != quote))
	{
		count++;
		(*i)++;
	}
	if (str[*i] == quote)
		(*i)++;
	return (count);
}

int	get_len_word(char *str, int start)
{
	int		i;
	int		count;

	count = 0;
	i = start;
	while (str[i] && str[i] != ' ' && str[i] != '\t'
		&& str[i] != '|' && str[i] != '<' && str[i] != '>')
	{
		if (str[i] == '\'' || str[i] == '"')
			count += count_inside_quotes(str, &i);
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}
