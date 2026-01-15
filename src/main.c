/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:27:28 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/15 17:43:22 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static void	create_min_env(t_mini *mini)
{
	char	*pwd;

	mini->has_env = 0;
	if (!mini->env)
	{
		mini->env = malloc(sizeof(char *));
		if (!mini->env)
			return ;
		mini->env[0] = NULL;
	}
	pwd = getcwd(NULL, 0);
	set_env(mini, "PWD", pwd);
	set_env(mini, "SHLVL", "1");
	set_env(mini, "PATH",
		"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:"
		"/home/alejandj/.local/bin");
}

static void	init_mini(char **argv, char **env, t_mini *mini)
{
	(void)argv;
	if (!env || !env[0])
		create_min_env(mini);
	else
	{
		mini->env = copy_env(env);
		mini->has_env = 1;
	}
	mini->exit_code = 0;
	mini->last_command = ft_strdup("./minishell");
	mini->arr_path = NULL;
	mini->prompt = NULL;
	mini->line = NULL;
	init_signals();
}

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

static void	handle_line(t_mini *mini)
{
	char			**tokens;
	t_token_info	*t_info;
	t_list			*cmd_list;
	char			*invalid;
	int				is_bonus;

	if (check_unclosed_quotes(mini->line))
	{
		print_cmd_error("syntax error", ": unclosed quotes");
		return ;
	}
	if (count_tokens(mini->line) == 0)
		return ;
	t_info = malloc(count_tokens(mini->line) * sizeof(t_token_info));
	if (!t_info)
		return ;
	tokens = split_tokens(mini->line, &t_info);
	if (!tokens)
	{
		free(t_info);
		return ;
	}
	is_bonus = 0;
	if (check_invalid_tokens(t_info, mini, &invalid, &is_bonus))
	{
		free(t_info);
        ft_free_wa(tokens);
		print_unexpected_error(mini, is_bonus, invalid);
		return ;
	}
	cmd_list = create_cmd_list(mini->line, tokens, t_info);
	if (expand_cmd_list(cmd_list, mini))
	{
		ft_lstclear(&cmd_list, free_cmd_node);
		free(t_info);
        ft_free_wa(tokens);
		return ;
	}
	execute_commands(cmd_list, mini);
	
	// frees
	free(t_info);
	ft_free_wa(tokens);
	ft_lstclear(&cmd_list, free_cmd_node);
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
		if (g_sig_status != 0)
		{
			mini.exit_code = g_sig_status;
			g_sig_status = 0;
		}
		if (!mini.line)
			return (ft_printf("exit\n"), rl_clear_history(), free_mini(&mini), 0);
		if (mini.line[0] == '\0')
		{
    		free(mini.line);
    		continue;
		}
		add_history(mini.line);
		handle_line(&mini);
		free(mini.line);
		mini.line = NULL;
	}
	return (0);
}
