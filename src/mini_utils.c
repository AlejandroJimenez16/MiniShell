/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 19:43:51 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/20 21:35:19 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	print_cmd_error(char *cmd, char *target, char *error)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
		ft_putstr_fd(cmd, 2);
	if (target)
	{
		ft_putstr_fd("'", 2);
		ft_putstr_fd(target, 2);
		ft_putstr_fd("': ", 2);
	}
	ft_putendl_fd(error, 2);
}

void	print_unexpected_error(t_mini *mini, int is_bonus, char *invalid)
{
	if (is_bonus)
	{
		ft_putstr_fd("minishell: operator '", 2);
		ft_putstr_fd(invalid, 2);
		ft_putendl_fd("' is not supported in this part", 2);
	}
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
		ft_putstr_fd(invalid, 2);
		ft_putendl_fd("'", 2);
	}
	mini->exit_code = 2;
}

int	get_cmd_arr_size(char **tokens, t_token_info *t_info, int start)
{
	int	i;
	int	count;

	i = start;
	count = 0;
	while (tokens[i] && t_info[i].type_token != PIPE)
	{
		if (t_info[i].type_token == WORD)
		{
			if (i == 0 || !is_redir(t_info[i - 1].type_token))
				count++;
		}
		i++;
	}
	return (count);
}

int	get_num_nodes(char *line, t_token_info *t_info)
{
	int	i;
	int	count;
	int	n_tokens;

	count = 0;
	n_tokens = count_tokens(line);
	i = 0;
	while (i < n_tokens)
	{
		if (t_info[i].type_token == PIPE)
			count++;
		i++;
	}
	return (count + 1);
}

int	is_redir(int type)
{
	if (type == REDIR_IN || type == REDIR_OUT
		|| type == REDIR_APPEND || type == HEREDOC)
		return (1);
	return (0);
}
