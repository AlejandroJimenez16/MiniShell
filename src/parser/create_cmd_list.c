/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:56:44 by alejandj          #+#    #+#             */
/*   Updated: 2025/12/15 13:51:14 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static t_cmd	*init_node(int n_words)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->cmd = malloc((n_words + 1) * sizeof(char *));
	if (!node->cmd)
	{
		free(node);
		return (NULL);
	}
	node->cmd_size = n_words;
	node->infile = NULL;
	node->heredoc = 0;
	node->delimeter = NULL;
	node->outfile = NULL;
	node->append = 0;
	node->index_start_cmd = 0;
	return (node);
}

static void	assign_token_to_node(t_cmd *node, char *token,
		int prev_token, int *cmd_index)
{
	if (prev_token == REDIR_IN)
		node->infile = ft_strdup(token);
	else if (prev_token == REDIR_OUT)
		node->outfile = ft_strdup(token);
	else if (prev_token == REDIR_APPEND)
	{
		node->append = 1;
		node->outfile = ft_strdup(token);
	}
	else if (prev_token == HEREDOC)
	{
		node->heredoc = 1;
		node->delimeter = ft_strdup(token);
	}
	else
	{
		node->cmd[*cmd_index] = ft_strdup(token);
		(*cmd_index)++;
		node->cmd[*cmd_index] = NULL;
	}
}

static int	get_prev_token(t_token_info *t_info, int i)
{
	int	prev_token;

	if (i > 0)
		prev_token = t_info[i - 1].type_token;
	else
		prev_token = 0;
	return (prev_token);
}

static t_cmd	*create_node(char **tokens, t_token_info *t_info, int *i)
{
	t_cmd	*node;
	int		n_words;
	int		cmd_index;
	int		prev_token;

	n_words = get_cmd_arr_size(tokens, t_info, *i);
	node = init_node(n_words);
	cmd_index = 0;
	while (tokens[*i])
	{
		if (t_info[*i].type_token == PIPE)
		{
			(*i)++;
			break ;
		}
		if (t_info[*i].type_token == WORD)
		{
			prev_token = get_prev_token(t_info, *i);
			if (cmd_index == 0 && (*i == 0 || !is_redir(prev_token)))
				node->index_start_cmd = *i;
			assign_token_to_node(node, tokens[*i], prev_token, &cmd_index);
		}
		(*i)++;
	}
	return (node);
}

t_list	*create_cmd_list(char *line, char **tokens, t_token_info *t_info)
{
	t_list	*cmd_list;
	int		num_nodes;
	int		i;
	int		index;

	cmd_list = NULL;
	num_nodes = get_num_nodes(line, t_info);
	i = 0;
	index = 0;
	while (index < num_nodes)
	{
		ft_lstadd_back(&cmd_list, ft_lstnew(create_node(tokens, t_info, &i)));
		index++;
	}
	return (cmd_list);
}
