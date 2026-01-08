/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:56:44 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/07 14:49:46 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

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
