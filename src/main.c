/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:27:28 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/24 02:27:21 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static int	expand_cmd_list(t_list *cmd_list, t_mini *mini)
{
	t_list	*current;
	t_cmd	*node;

	current = cmd_list;
	while (current)
	{
		node = current->content;
		if (expand_vars(node, mini) == -1)
			return (1);
		current = current->next;
	}
	return (0);
}

static int	tokenize_and_validate(t_mini *mini)
{
	char	*invalid;
	int		n_tokens;

	if (check_unclosed_quotes(mini->line))
	{
		print_cmd_error(NULL, NULL, "syntax error: unclosed quotes");
		return (1);
	}
	n_tokens = count_tokens(mini->line);
	if (n_tokens == 0)
		return (1);
	mini->t_info = malloc(n_tokens * sizeof(t_token_info));
	if (!mini->t_info)
		return (1);
	mini->tokens = split_tokens(mini->line, &mini->t_info);
	if (!mini->tokens)
		return (free(mini->t_info), 1);
	if (check_invalid_tokens(mini->t_info, mini, &invalid))
	{
		print_unexpected_error(mini, invalid);
		free(mini->t_info);
		ft_free_wa(mini->tokens);
		return (1);
	}
	return (0);
}

static void	handle_line(t_mini *mini)
{
	if (tokenize_and_validate(mini))
		return ;
	mini->cmd_list = create_cmd_list(mini->line, mini->tokens, mini->t_info);
	if (!mini->cmd_list)
	{
		free(mini->t_info);
		ft_free_wa(mini->tokens);
		return ;
	}
	if (expand_cmd_list(mini->cmd_list, mini))
	{
		ft_lstclear(&mini->cmd_list, free_cmd_node);
		free(mini->t_info);
		ft_free_wa(mini->tokens);
		return ;
	}
	execute_commands(mini);
	free(mini->t_info);
	ft_free_wa(mini->tokens);
	ft_lstclear(&mini->cmd_list, free_cmd_node);
}

static int	check_line_state(t_mini *mini)
{
	if (mini->line[0] == '\0')
	{
		free(mini->line);
		return (1);
	}
	if (g_sig_status != 0)
	{
		mini->exit_code = g_sig_status;
		g_sig_status = 0;
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;

	if (argc != 1)
		return (ft_putendl_fd("minishell: no args supported", 2), 1);
	init_mini(argv, env, &mini);
	while (1)
	{
		mini.prompt = get_prompt(mini.has_env, mini.env);
		mini.line = readline(mini.prompt);
		free(mini.prompt);
		mini.prompt = NULL;
		if (!mini.line)
			return (ft_printf("exit\n"), free_mini(&mini), 0);
		if (check_line_state(&mini))
			continue ;
		ft_add_to_history(&mini);
		handle_line(&mini);
		free(mini.line);
	}
	return (0);
}
