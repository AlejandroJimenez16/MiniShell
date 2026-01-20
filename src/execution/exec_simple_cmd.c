/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:27:04 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/20 13:56:39 by alejandj         ###   ########.fr       */
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
	int		exit_code;
	char	*prefix;

	if (access(cmd[0], F_OK) != 0)
	{
		print_cmd_error(cmd[0], NULL, ": No such file or directory");
		exit_code = 127;
	}
	else if (access(cmd[0], X_OK) != 0)
	{
		print_cmd_error(cmd[0], NULL, ": Permission denied");
		exit_code = 126;
	}
	else
	{
		execve(cmd[0], cmd, mini->env);
		prefix = ft_strjoin(cmd[0], ": ");
		print_cmd_error(prefix, NULL, strerror(errno));
		free(prefix);
		exit_code = 126;
	}
	free_mini(mini);
	free(mini->t_info);
	ft_free_wa(mini->tokens);
	ft_lstclear(&mini->cmd_list, free_cmd_node);
	exit(exit_code);
}

static void	handle_cmd_error(char **cmd, t_mini *mini, int permission)
{
	if (!mini->arr_path || mini->arr_path[0] == NULL)
		print_cmd_error(cmd[0], NULL, ": No such file or directory");
	else if (permission)
		print_cmd_error(cmd[0], NULL, ": Permission denied");
	else
		print_cmd_error(cmd[0], NULL, ": command not found");
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
