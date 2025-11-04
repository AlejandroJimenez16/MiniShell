/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:27:28 by alejandj          #+#    #+#             */
/*   Updated: 2025/11/03 18:30:55 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	child_simple_cmd(t_mini *mini)
{
	int		arr_path_id;
	char	*path;

	mini->simple_cmd_process = fork();
	if (mini->simple_cmd_process < 0)
	{
		perror("fork");
		return ;
	}
	else if (mini->simple_cmd_process == 0)
	{
		arr_path_id = 0;
		while (mini->arr_path && (mini->arr_path[arr_path_id] != NULL))
		{
			path = mini->arr_path[arr_path_id++];
			create_path(&path, mini->cmd[0]);
			if (access(path, X_OK) == 0)
				execve(path, mini->cmd, mini->env);
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;

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

		if (ft_strchr(mini.line, '|'))
		{
			printf("hola que tal");
			ft_pipex_exec(mini.cmd, mini.env);
		}
		else
		{
			mini.cmd = ft_split(mini.line, ' ');
			/*
			if (!mini.cmd)
			{
				
			}
			*/
			if (mini.cmd && mini.cmd[0] && ft_strncmp(mini.cmd[0], "cd", 3) == 0)
				ft_cd(&mini);
			else
			{
				child_simple_cmd(&mini);
				waitpid(mini.simple_cmd_process, NULL, 0);
			}
			free_tab(mini.cmd);
		}
		free(mini.line);
	}
	return (0);
}
