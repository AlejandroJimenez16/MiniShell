/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:27:28 by alejandj          #+#    #+#             */
/*   Updated: 2025/11/06 14:13:34 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	handle_builtin(t_mini *mini)
{
	if (mini->cmd && mini->cmd[0])
	{
		if (ft_strncmp(mini->cmd[0], "cd", 3) == 0)
		{
			ft_cd(mini);
			return (1);
		}	
		else if (ft_strncmp(mini->cmd[0], "pwd", 3) == 0)
		{
			ft_pwd();
			return (1);
		}
		else if (ft_strncmp(mini->cmd[0], "env", 3) == 0)
		{
			ft_env(mini->env);
			return (1);
		}
	}
	return (0);
}

void	child_simple_cmd(t_mini *mini)
{
	mini->simple_cmd_process = fork();
	if (mini->simple_cmd_process < 0)
	{
		perror("fork");
		return ;
	}
	else if (mini->simple_cmd_process == 0)
		execute_simple_commands(mini);
}

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;
	int		status;

	if (argc != 1)
		return (ft_putendl_fd("minishell: no args supported", 2), 1);
	(void)argv;
	mini.env = env;
	mini.arr_path = get_path_cmd(env);
	while (1)
	{
		mini.prompt = get_prompt(env);
		mini.line = readline(mini.prompt);
		if (!mini.line)
			return (ft_printf("exit\n"), 0);
		add_history(mini.line);

		/*
		if (ft_strchr(mini.line, '|'))
		{
			printf("hola que tal");
			ft_pipex_exec(mini.cmd, mini.env);
		}
		*/
		//else
		//{
			mini.cmd = ft_split(mini.line, ' ');
			if (!mini.cmd)
			{
				ft_free_wa(mini.arr_path);
				free(mini.line);
				clear_history();
				return (1);
			}
			if (!handle_builtin(&mini))
			{
				child_simple_cmd(&mini);
				waitpid(mini.simple_cmd_process, &status, 0);
				mini.last_status = WEXITSTATUS(status);
			}
			free_tab(mini.cmd);
		//}
		free(mini.line);
	}
	free(mini.prompt);
	return (0);
}
