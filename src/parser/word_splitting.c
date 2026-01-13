/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:27:48 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/13 16:36:41 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	has_separators(char *tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i] == ' ' || tokens[i] == '\t' || tokens[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static void	normalize_split(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\t' || str[i] == '\n')
			str[i] = ' ';
		i++;
	}
}

static int	copy_arr_to_cmd(char **arr, t_fill_cmds *f_cmds, int old_i, int i)
{
	int	index_arr;

	if (old_i == i)
	{
		index_arr = 0;
		while (arr[index_arr])
		{
			f_cmds->new_cmd[f_cmds->new_i] = ft_strdup(arr[index_arr]);
			f_cmds->new_cmd_quotes[f_cmds->new_i] = NO_QUOTES;
			index_arr++;
			f_cmds->new_i++;
		}
		return (1);
	}
	return (0);
}

static int	create_fill_new_cmd(t_cmd *node, char **arr, int n_cmds, int i)
{
	t_fill_cmds		f_cmds;
	int				old_i;

	f_cmds.new_cmd = malloc((n_cmds + 1) * sizeof(char *));
	if (!f_cmds.new_cmd)
		return (1);
	f_cmds.new_cmd_quotes = malloc((n_cmds + 1) * sizeof(t_quote_type));
	if (!f_cmds.new_cmd_quotes)
		return (free(f_cmds.new_cmd), 1);
	old_i = 0;
	f_cmds.new_i = 0;
	while (old_i < node->cmd_size)
	{
		if (copy_arr_to_cmd(arr, &f_cmds, old_i, i))
			old_i++;
		else
		{
			f_cmds.new_cmd[f_cmds.new_i] = node->cmd[old_i];
			f_cmds.new_cmd_quotes[f_cmds.new_i++] = node->cmd_quotes[old_i++];
		}
	}
	f_cmds.new_cmd[f_cmds.new_i] = NULL;
	node->cmd_size = n_cmds;
	node->cmd = f_cmds.new_cmd;
	return (node->cmd_quotes = f_cmds.new_cmd_quotes, 0);
}

int	word_splitting(t_cmd *node, char *result, int i)
{
	char	**arr;
	int		n_arr;
	int		n_cmds;

	normalize_split(result);
	arr = ft_split(result, ' ');
	if (!arr)
		return (-1);
	n_arr = 0;
	while (arr[n_arr])
		n_arr++;
	n_cmds = n_arr + (node->cmd_size - 1);
	if (create_fill_new_cmd(node, arr, n_cmds, i))
		return (-1);
	ft_free_wa(arr);
	return (n_arr);
}
