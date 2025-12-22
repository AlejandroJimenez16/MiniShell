/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 19:43:51 by alejandj          #+#    #+#             */
/*   Updated: 2025/12/22 15:14:46 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	print_cmd_error(char *cmd, char *error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(error, 2);
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
