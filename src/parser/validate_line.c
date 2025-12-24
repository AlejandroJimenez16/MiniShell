/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 20:14:22 by alejandj          #+#    #+#             */
/*   Updated: 2025/12/25 00:52:23 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	check_unclosed_quotes(char *line)
{
	int	i;
	int	single_quotes;
	int	double_quotes;

	single_quotes = 0;
	double_quotes = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '"' && !single_quotes)
			double_quotes = !double_quotes;
		if (line[i] == '\'' && !double_quotes)
			single_quotes = !single_quotes;
		i++;
	}
	if (double_quotes || single_quotes)
		return (1);
	return (0);
}

int	check_invalid_tokens(t_token_info *t_info, t_mini *mini)
{
	int	n_tokens;
	int	last;

	n_tokens = count_tokens(mini->line);
	last = n_tokens - 1;
	if (n_tokens == 1)
	{
		if (t_info[0].type_token == PIPE)
			return (1);
		if (is_redir(t_info[0].type_token))
			return (1);
	}
	if (t_info[0].type_token == PIPE)
		return (1);
	if (t_info[last].type_token == PIPE || is_redir(t_info[last].type_token))
		return (1);
	return (0);
}
