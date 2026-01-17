/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:28:24 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/17 19:16:11 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	free_mini(t_mini *mini)
{
	if (mini->env)
		ft_free_wa(mini->env);
	if (mini->last_command)
		free(mini->last_command);
	if (mini->prompt)
		free(mini->prompt);
	if (mini->line)
		free(mini->line);
	if (mini->arr_path)
		ft_free_wa(mini->arr_path);
	if (mini->t_info)
		free(mini->t_info);
	if (mini->tokens)
		ft_free_wa(mini->tokens);
	if (mini->cmd_list)
		ft_lstclear(&mini->cmd_list, free_cmd_node);
	rl_clear_history();
}

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
	if (node->cmd_quotes)
		free(node->cmd_quotes);
	if (node->redirs)
		ft_lstclear(&node->redirs, free_redir);
	free(node);
}


