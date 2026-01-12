/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:27:48 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/12 21:43:14 by alejandj         ###   ########.fr       */
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

static char	**create_fill_new_cmd(t_cmd *node, char **arr, int n_cmds, int i)
{
	char	**new_cmd;
	int		old_i;
	int		new_i;
	int		index_arr;

	new_cmd = malloc((n_cmds + 1) * sizeof(char *));
	if (!new_cmd)
		return (NULL);
	old_i = 0;
	new_i = 0;
	while (old_i < node->cmd_size)
	{
		if (old_i == i)
		{
			index_arr = 0;
			while (arr[index_arr])
				new_cmd[new_i++] = ft_strdup(arr[index_arr++]);
			old_i++;
		}
		else
			new_cmd[new_i++] = node->cmd[old_i++];
	}
	new_cmd[new_i] = NULL;
	return (new_cmd);
}

int	word_splitting(t_cmd *node, char *result, int i)
{
	char	**arr;
	int		n_arr;
	int		n_cmds;
	char	**new_cmd;

	normalize_split(result);
	arr = ft_split(result, ' ');
	if (!arr)
		return (-1);
	n_arr = 0;
	while (arr[n_arr])
		n_arr++;
	n_cmds = n_arr + (node->cmd_size - 1);
	new_cmd = create_fill_new_cmd(node, arr, n_cmds, i);
	if (!new_cmd)
		return (-1);
	node->cmd_size = n_cmds;
	ft_free_wa(arr);
	node->cmd = new_cmd;
	return (n_arr);
}
