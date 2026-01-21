/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:27:04 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/22 00:11:15 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static void	execute_absolute_path(char **cmd, t_mini *mini)
{
	if (access(cmd[0], F_OK) != 0)
	{
		print_cmd_error(cmd[0], NULL, ": No such file or directory");
		mini->exit_code = 127;
	}
	else if (access(cmd[0], X_OK) != 0)
	{
		print_cmd_error(cmd[0], NULL, ": Permission denied");
		mini->exit_code = 126;
	}
	else
	{
		execve(cmd[0], cmd, mini->env);
		print_exec_error(mini, cmd, NULL);
	}
}

static int	try_execve(char *path, char **cmd, t_mini *mini)
{
	if (access(path, X_OK) == 0)
	{
		execve(path, cmd, mini->env);
		print_exec_error(mini, cmd, path);
		free(path);
		return (1);
	}
	return (0);
}

static void	execute_from_path(char **cmd, t_mini *mini)
{
	int		permission;
	int		i;
	char	*path;
	char	*path_permission;

	i = 0;
	permission = 0;
	path_permission = NULL;
	mini->arr_path = get_path_cmd(mini->env);
	while (mini->arr_path && (mini->arr_path[i] != NULL))
	{
		path = ft_strdup(mini->arr_path[i++]);
		create_path(&path, cmd[0]);
		if (access(path, F_OK) == 0)
		{
			if (try_execve(path, cmd, mini))
				return ;
			if (!path_permission)
				path_permission = ft_strdup(path);
			permission = 1;
		}
		free(path);
	}
	handle_cmd_error(cmd, mini, permission, path_permission);
}

void	execute_simple_commands(char **cmd, t_mini *mini)
{
	if (!cmd || !cmd[0] || !cmd[0][0])
		return ;
	else if (cmd[0][0] == '.' || cmd[0][0] == '/')
		execute_absolute_path(cmd, mini);
	else
		execute_from_path(cmd, mini);
}
