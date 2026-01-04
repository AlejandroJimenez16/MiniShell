/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:28:24 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/04 21:33:59 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	free_redir(void *content)
{
	t_redir	*redir;

	redir = (t_redir *)content;
	if (redir)
	{
		if (redir->file)
			free(redir->file);
		free(redir);
	}
}

void	free_cmd_node(void *context)
{
	t_cmd	*node;

	node = (t_cmd *)context;
	if (!node)
		return ;
	if (node->cmd)
		ft_free_wa(node->cmd);
	if (node->redirs)
		ft_lstclear(&node->redirs, free_redir);
	free(node);
}
