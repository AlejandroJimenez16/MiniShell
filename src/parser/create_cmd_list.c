/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:56:44 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/22 18:06:57 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static t_cmd	*create_node(char **tokens, t_token_info *t_info, int *i)
{
	t_cmd	*node;
	int		n_words;

	n_words = get_cmd_arr_size(tokens, t_info, *i);
	node = init_node(n_words);
	if (!node)
		return (NULL);
	while (tokens[*i])
	{
		if (t_info[*i].type_token == PIPE)
		{
			(*i)++;
			break ;
		}
		if (t_info[*i].type_token == WORD)
		{
			if (assign_token_to_node(node, tokens[*i], t_info, i))
			{
				free_cmd_node(node);
				return (NULL);
			}
		}
		(*i)++;
	}
	return (node);
}

t_list	*create_cmd_list(char *line, char **tokens, t_token_info *t_info)
{
	t_list	*cmd_list;
	t_cmd	*cmd_node;
	t_list	*new_node;
	int		i;
	int		index;

	cmd_list = NULL;
	i = 0;
	index = 0;
	while (index < get_num_nodes(line, t_info))
	{
		cmd_node = create_node(tokens, t_info, &i);
		if (!cmd_node)
			return (ft_lstclear(&cmd_list, free_cmd_node), NULL);
		new_node = ft_lstnew(cmd_node);
		if (!new_node)
		{
			free_cmd_node(cmd_node);
			ft_lstclear(&cmd_list, free_cmd_node);
			return (NULL);
		}
		ft_lstadd_back(&cmd_list, new_node);
		index++;
	}
	return (cmd_list);
}
