/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:27:04 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/09 12:23:13 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static void	create_path(char **s1, char *s2)
{
	char	*new_string;

	new_string = ft_strjoin(*s1, "/");
	free(*s1);
	*s1 = ft_strjoin(new_string, s2);
	free(new_string);
}

static void	execute_absolute_path(char **cmd, t_mini *mini)
{
	int	exit_code;

	if (access(cmd[0], F_OK) != 0)
	{
		print_cmd_error(cmd[0], ": No such file or directory");
		exit_code = 127;
	}
	else if (access(cmd[0], X_OK) != 0)
	{
		print_cmd_error(cmd[0], ": Permission denied");
		exit_code = 126;
	}
	else
	{
		execve(cmd[0], cmd, mini->env);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		exit_code = 126;
	}
	if (mini->arr_path)
	{
		ft_free_wa(mini->arr_path);
		mini->arr_path = NULL;
	}
	free_mini(mini);
	ft_lstclear(&mini->cmd_list, free_cmd_node);
	exit(exit_code);
}

static void	handle_cmd_error(char **cmd, t_mini *mini, int permission)
{
	if (!mini->arr_path || mini->arr_path[0] == NULL)
		print_cmd_error(cmd[0], ": No such file or directory");
	else if (permission)
		print_cmd_error(cmd[0], ": Permission denied");
	else
		print_cmd_error(cmd[0], ": command not found");
	if (mini->arr_path)
	{
		ft_free_wa(mini->arr_path);
		mini->arr_path = NULL;
	}
	free_mini(mini);
	ft_lstclear(&mini->cmd_list, free_cmd_node);
	if (permission)
		exit(126);
	exit(127);
}

static void	execute_from_path(char **cmd, t_mini *mini)
{
	int		permission;
	int		i;
	char	*path;

	i = 0;
	permission = 0;
	mini->arr_path = get_path_cmd(mini->env);
	while (mini->arr_path && (mini->arr_path[i] != NULL))
	{
		path = ft_strdup(mini->arr_path[i++]);
		create_path(&path, cmd[0]);
		if (access(path, F_OK) == 0)
		{
			if (access(path, X_OK) == 0)
				execve(path, cmd, mini->env);
			else
				permission = 1;
		}
		free(path);
	}
	handle_cmd_error(cmd, mini, permission);
	ft_free_wa(mini->arr_path);
	mini->arr_path = NULL;
}

void	execute_simple_commands(char **cmd, t_mini *mini)
{
	if (!cmd || !cmd[0] || !cmd[0][0])
		exit(0);
	else if (cmd[0][0] == '.' || cmd[0][0] == '/')
		execute_absolute_path(cmd, mini);
	else
		execute_from_path(cmd, mini);
}
