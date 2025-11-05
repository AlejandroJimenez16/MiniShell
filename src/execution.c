/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:27:04 by alejandj          #+#    #+#             */
/*   Updated: 2025/11/05 19:22:38 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	execute_absolute_path(t_mini *mini)
{
	if (access(mini->cmd[0], F_OK) != 0)
	{
		print_cmd_error(mini->cmd[0], ": command not found\n");
		exit(127);
	}
	else if (access(mini->cmd[0], X_OK) != 0)
	{
		print_cmd_error(mini->cmd[0], ": Permission denied\n");
		exit(126);
	}
	else
	{
		execve(mini->cmd[0], mini->cmd, mini->env);
		print_cmd_error(mini->cmd[0], ": Exec format error\n");
		exit(126);
	}
}

void	manage_error_msg(t_mini *mini, int permission)
{
	if (permission)
	{
		print_cmd_error(mini->cmd[0], ": Permission denied\n");
		exit(126);
	}
	else
	{
		print_cmd_error(mini->cmd[0], ": command not found\n");
		exit(127);
	}
}

void	execute_from_path(t_mini *mini)
{
	int		permission;
	int		i;
	char	*path;

	i = 0;
	permission = 0;
	while (mini->arr_path && (mini->arr_path[i] != NULL))
	{
		path = ft_strdup(mini->arr_path[i++]);
		create_path(&path, mini->cmd[0]);
		if (access(path, F_OK) == 0)
		{
			if (access(path, X_OK) == 0)
				execve(path, mini->cmd, mini->env);
			else
				permission = 1;
		}
		free(path);
	}
	manage_error_msg(mini, permission);
}

void	execute_simple_commands(t_mini *mini)
{
	if (!mini->cmd || !mini->cmd[0] || !mini->cmd[0][0])
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("", 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	else if (mini->cmd[0][0] == '.' || mini->cmd[0][0] == '/')
		execute_absolute_path(mini);
	else
		execute_from_path(mini);
}
