/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:58:25 by alejandj          #+#    #+#             */
/*   Updated: 2025/12/03 21:48:50 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

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
