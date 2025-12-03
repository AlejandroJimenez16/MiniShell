/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:58:25 by alejandj          #+#    #+#             */
/*   Updated: 2025/12/03 20:17:21 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	count_tokens(char *str)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	while (str[i])
	{
		// Saltar espacios
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		if (!str[i])
			break ;

		// Comillas
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			count++;
			while (str[i] && (str[i] != quote))
				i++;
			if (str[i] == quote)
				i++;
		}
		// Redirecciones y pipes
		else if (str[i] == '|' || str[i] == '<' || str[i] == '>')
		{
			count++;
			if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>'))
				i++;
			i++;
		}
		// Palabra normal
		else
		{
			count++;
			while (str[i] && (str[i] != ' ' && str[i] != '\t'
					&& str[i] != '|' && str[i] != '<' && str[i] != '>'))
				i++;
		}
	}
	return (count);
}

void	set_token_type(char *token, t_token_info *t_info)
{
	if (ft_strncmp(token, "<<", 2) == 0)
    	t_info->type_token = HEREDOC;
	else if (ft_strncmp(token, ">>", 2) == 0)
		t_info->type_token = REDIR_APPEND;
	else if (ft_strncmp(token, "<", 1) == 0)
		t_info->type_token = REDIR_IN;
	else if (ft_strncmp(token, ">", 1) == 0)
    	t_info->type_token = REDIR_OUT;
	else if (ft_strncmp(token, "|", 1) == 0)
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
