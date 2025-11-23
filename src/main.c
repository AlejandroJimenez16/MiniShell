/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:27:28 by alejandj          #+#    #+#             */
/*   Updated: 2025/11/23 21:54:21 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static void	handle_simple_commands(t_mini *mini)
{
	t_token_info	*t_info;
	int				status;
	
	t_info = malloc(count_tokens(mini->line) * sizeof(t_token_info));
	if (!t_info)
		return ;
	mini->cmd = split_tokens(mini->line, &t_info);
	if (!mini->cmd)
	{
		ft_free_wa(mini->arr_path);
		free(mini->line);
		clear_history();
		return ;
	}
	expand_vars(mini, t_info);
	if (!is_builtin(mini->cmd))
	{
		child_simple_cmd(mini);
		waitpid(mini->simple_cmd_process, &status, 0);
		mini->exit_code = WEXITSTATUS(status);
	}
	else
		exec_builtins(mini);
	ft_free_wa(mini->cmd);
}

static void	handle_line(t_mini *mini)
{
	char	**parsed_argv;

	if (!mini->line || *mini->line == '\0')
		return ;
	if (ft_strchr(mini->line, '|'))
	{
		printf("Pipex\n");
		parsed_argv = parse_line(mini->line);
		if (!parsed_argv)
			return ;
		execute_pipex(count_items(parsed_argv), parsed_argv, mini->env);
		ft_free_wa(parsed_argv);
	}
	else
		handle_simple_commands(mini);
}

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;

	if (argc != 1)
		return (ft_putendl_fd("minishell: no args supported", 2), 1);
	(void)argv;
	mini.env = env;
	mini.arr_path = get_path_cmd(mini.env);
	while (1)
	{
		mini.prompt = get_prompt(mini.env);
		mini.line = readline(mini.prompt);
		if (!mini.line)
			return (ft_printf("exit\n"), 0);
		add_history(mini.line);
		handle_line(&mini);
		free(mini.line);
	}
	free(mini.prompt);
	return (0);
}
