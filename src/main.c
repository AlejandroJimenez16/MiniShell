/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:27:28 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/02 13:59:24 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static void	init_mini(char **argv, char **env, t_mini *mini)
{
	(void)argv;
	mini->env = copy_env(env);
	mini->exit_code = 0;
	mini->last_command = ft_strdup("./minishell");
	init_signals();
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
	t_info = malloc(count_tokens(mini->line) * sizeof(t_token_info));
	if (!t_info)
		return ;
	tokens = split_tokens(mini->line, &t_info);
	if (!tokens)
		return ;
	is_bonus = 0;
	if (check_invalid_tokens(t_info, mini, &invalid, &is_bonus))
	{
		print_unexpected_error(mini, is_bonus, invalid);
		return ;
	}
	cmd_list = create_cmd_list(mini->line, tokens, t_info);
	execute_commands(cmd_list, mini, t_info);
}

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;

	if (argc != 1)
		return (ft_putendl_fd("minishell: no args supported", 2), 1);
	init_mini(argv, env, &mini);
	while (1)
	{
		if (g_sig_status != 0)
		{
			mini.exit_code = g_sig_status;
			g_sig_status = 0;
		}
		mini.prompt = get_prompt(mini.env);
		mini.line = readline(mini.prompt);
		if (!mini.line)
			return (ft_printf("exit\n"), 0);
		add_history(mini.line);
		handle_line(&mini);
		//set_env("VAR", "\"mun'do\"", mini.env);
		free(mini.line);
	}
	return (free(mini.prompt), 0);
}
