/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 21:42:30 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/08 19:28:49 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

char	*expand_vars_in_token(t_mini *mini, char *arg)
{
	char	*result;
	int		i;
	int		i_result;
	int		len;

	len = get_len_token(mini, arg);
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	i_result = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i + 1] == '?')
			i_result += handle_exit_code_copy(mini, result + i_result, &i);
		else if (arg[i] == '$' && arg[i + 1] == '_'
			&& !(ft_isalnum(arg[i + 2]) || arg[i + 2] == '_'))
			i_result += handle_last_command_copy(mini, result + i_result, &i);
		else if (arg[i] == '$' && (ft_isalpha(arg[i + 1]) || arg[i + 1] == '_'))
			i_result += handle_env_var_copy(mini, arg, &i, result + i_result);
		else
			result[i_result++] = arg[i++];
	}
	result[i_result] = '\0';
	return (result);
}

static void	expand_redir(t_cmd *node, t_mini *mini)
{
	t_list	*redir_lst;
	t_redir	*redir;
	char	*temp;

	redir_lst = node->redirs;
	while (redir_lst)
	{
		redir = (t_redir *)redir_lst->content;
		if ((redir->type == REDIR_IN || redir->type == REDIR_OUT
				|| redir->type == REDIR_APPEND)
			&& redir->quote != SINGLE_QUOTES)
		{
			temp = redir->file;
			redir->file = expand_vars_in_token(mini, redir->file);
			free(temp);
		}
		redir_lst = redir_lst->next;
	}
}

void	expand_vars(t_cmd *node, t_mini *mini)
{
	int		i;
	char	*temp;

	if (!node->cmd || !node->cmd[0] || !node->cmd[0][0])
		return ;
	expand_redir(node, mini);
	i = 0;
	while (node->cmd[i])
	{
		if (node->cmd_quotes[i] != SINGLE_QUOTES)
		{
			temp = node->cmd[i];
			node->cmd[i] = expand_vars_in_token(mini, node->cmd[i]);
			free(temp);
		}
		i++;
	}
}
