/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 20:14:22 by alejandj          #+#    #+#             */
/*   Updated: 2026/02/05 21:02:53 by alejandj         ###   ########.fr       */
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

static void	choose_redir(int redir, char **invalid)
{
	if (redir == REDIR_IN)
		*invalid = "<";
	else if (redir == REDIR_OUT)
		*invalid = ">";
	else if (redir == HEREDOC)
		*invalid = "<<";
	else if (redir == REDIR_APPEND)
		*invalid = ">>";
}

static int	check_multiple_tokens(t_token_info *t_info, t_mini *mini,
		char **invalid)
{
	int	i;
	int	n_tokens;
	int	last;

	n_tokens = count_tokens(mini->line);
	last = n_tokens - 1;
	i = 0;
	while (i < last)
	{
		if (t_info[i + 1].type_token == PIPE && is_redir(t_info[i].type_token))
			return (*invalid = "|", 1);
		if (t_info[i].type_token == PIPE && is_redir(t_info[i + 1].type_token))
			return (choose_redir(t_info[i + 1].type_token, invalid), 1);
		if (t_info[i].type_token == PIPE && t_info[i + 1].type_token == PIPE)
			return (*invalid = "|", 1);
		if (is_redir(t_info[i].type_token)
			&& is_redir(t_info[i + 1].type_token))
			return (choose_redir(t_info[i + 1].type_token, invalid), 1);
		i++;
	}
	return (0);
}

int	check_invalid_tokens(t_token_info *t_info, t_mini *mini,
		char **invalid)
{
	int	n_tokens;
	int	last;

	n_tokens = count_tokens(mini->line);
	last = n_tokens - 1;
	if (last < 0)
		return (0);
	if (check_multiple_tokens(t_info, mini, invalid))
		return (1);
	if (t_info[0].type_token == PIPE)
		return (*invalid = "|", 1);
	if (t_info[last].type_token == PIPE || is_redir(t_info[last].type_token))
	{
		if (t_info[last].type_token == PIPE)
			return (*invalid = "|", 1);
		else
			return (*invalid = "newline", 1);
	}
	return (0);
}
