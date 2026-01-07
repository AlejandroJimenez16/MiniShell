/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:56:44 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/07 14:10:16 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static t_cmd	*init_node(int n_words)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	if (n_words > 0)
	{
		node->cmd = malloc((n_words + 1) * sizeof(char *));
		if (!node->cmd)
		{
			free(node);
			return (NULL);
		}
		node->cmd_quotes = malloc((n_words + 1) * sizeof(t_quote_type));
		if (!node->cmd_quotes)
		{
			free(node->cmd);
			free(node);
			return (NULL);
		}
	}
	else
	{
		node->cmd = NULL;
		node->cmd_quotes = NULL;
	}
	node->cmd_index = 0;
	node->cmd_size = n_words;
	node->redirs = NULL;
	return (node);
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

static void	assign_token_to_node(t_cmd *node, char *token,
		t_token_info *t_info, int *i)
{
	t_redir	*redir;
	t_list	*new_node;
	int		prev_token;

	prev_token = get_prev_token(t_info, *i);
	if (is_redir(prev_token))
	{
		redir = malloc(sizeof(t_redir));
		if (!redir)
			return ;
		redir->type = prev_token;
		redir->file = ft_strdup(token);
		redir->quote = t_info[*i].type_quote;
		new_node = ft_lstnew(redir);
		if (!new_node)
		{
			free(redir->file);
			free(redir);
			return ;
		}
		ft_lstadd_back(&node->redirs, new_node);
	}
	else
	{
		node->cmd[node->cmd_index] = ft_strdup(token);
		node->cmd_quotes[node->cmd_index] = t_info[*i].type_quote;
		node->cmd_index++;
		node->cmd[node->cmd_index] = NULL;
	}
}

static t_cmd	*create_node(char **tokens, t_token_info *t_info, int *i)
{
	t_cmd	*node;
	int		n_words;

	n_words = get_cmd_arr_size(tokens, t_info, *i);
	node = init_node(n_words);
	while (tokens[*i])
	{
		if (t_info[*i].type_token == PIPE)
		{
			(*i)++;
			break ;
		}
		if (t_info[*i].type_token == WORD)
			assign_token_to_node(node, tokens[*i], t_info, i);
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
