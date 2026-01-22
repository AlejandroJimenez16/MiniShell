/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_list_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 14:35:06 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/22 18:14:12 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static int	alloc_node_arrays(t_cmd *node, int n_words)
{
	node->cmd = malloc((n_words + 1) * sizeof(char *));
	if (!node->cmd)
		return (1);
	node->cmd_quotes = malloc((n_words + 1) * sizeof(t_quote_type));
	if (!node->cmd_quotes)
	{
		free(node->cmd);
		return (1);
	}
	return (0);
}

t_cmd	*init_node(int n_words)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	if (n_words > 0)
	{
		if (alloc_node_arrays(node, n_words))
		{
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

int	add_redir_to_node(t_cmd *node, int prev_token,
		char *token, t_quote_type type_quote)
{
	t_redir	*redir;
	t_list	*new_node;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (1);
	redir->type = prev_token;
	redir->file = ft_strdup(token);
	redir->quote = type_quote;
	new_node = ft_lstnew(redir);
	if (!new_node)
	{
		free(redir->file);
		free(redir);
		return (1);
	}
	ft_lstadd_back(&node->redirs, new_node);
	return (0);
}

int	assign_token_to_node(t_cmd *node, char *token,
		t_token_info *t_info, int *i)
{
	int		prev_token;

	prev_token = get_prev_token(t_info, *i);
	if (is_redir(prev_token))
	{
		if (add_redir_to_node(node, prev_token, token, t_info[*i].type_quote))
			return (1);
	}
	else
	{
		node->cmd[node->cmd_index] = ft_strdup(token);
		node->cmd_quotes[node->cmd_index] = t_info[*i].type_quote;
		node->cmd_index++;
		node->cmd[node->cmd_index] = NULL;
	}
	return (0);
}

int	get_prev_token(t_token_info *t_info, int i)
{
	int	prev_token;

	if (i > 0)
		prev_token = t_info[i - 1].type_token;
	else
		prev_token = 0;
	return (prev_token);
}
