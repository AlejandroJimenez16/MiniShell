/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:27:28 by alejandj          #+#    #+#             */
/*   Updated: 2025/10/31 20:00:53 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

char	*create_path(char *base, char *cmd)
{
	char *temp;
	char *full;

	temp = ft_strjoin(base, "/");
	full = ft_strjoin(temp, cmd);
	return (full);
}

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
			path = create_path(mini->arr_path[arr_path_id++], mini->cmd[0]);
			if (access(path, X_OK) == 0)
				execve(path, mini->cmd, mini->env);
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;

	if (argc == 1)
	{
		// Ignorar argv
		(void)argv;
		mini.env = env;
		mini.arr_path = get_path_cmd(env);

		// Bucle que muestra prompt
		while (1)
		{
			mini.prompt = get_prompt(env);
			mini.line = readline(mini.prompt);
			if (!mini.line) // Ctrl+D
			{
				ft_printf("exit\n");
				exit(0);
			}
			add_history(mini.line);

			mini.cmd = ft_split(mini.line, ' ');
			if (!mini.cmd || !mini.cmd[0])
				continue ;

			if (ft_strncmp(mini.cmd[0], "cd", 3) == 0)
			{
				ft_cd(mini.cmd[1]);
				//Limpiar mini.cmd con free_tab(mini.cmd);
				continue ;
			}

			// Ejecucion comandos simples
			child_simple_cmd(&mini);
			
			waitpid(mini.simple_cmd_process, NULL, 0);
		}
	}
	else
	{
		ft_putendl_fd("minishell: no args supported", 2);
		return (1);
	}
}
