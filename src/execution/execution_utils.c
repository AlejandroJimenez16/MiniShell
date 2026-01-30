/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:58:34 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/30 15:36:43 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	handle_child(t_cmd *node, t_mini *mini, t_pipex *pipex)
{
	if (mini->history_fd != -1)
		close(mini->history_fd);
	setup_child_signals();
	if (handle_redirections(node, pipex, mini))
		return (mini->exit_code);
	if (pipex->pipefd[0] != -1)
		close(pipex->pipefd[0]);
	if (pipex->pipefd[1] != -1)
		close(pipex->pipefd[1]);
	if (pipex->prev_pipe_in != -1)
		close(pipex->prev_pipe_in);
	if (is_builtin(node->cmd))
		return (exec_builtins(node->cmd, mini));
	else
		execute_simple_commands(node->cmd, mini);
	return (mini->exit_code);
}

void	handle_parent(t_pipex *pipex, t_mini *mini, t_cmd *node)
{
	if (pipex->prev_pipe_in != -1)
	{
		close(pipex->prev_pipe_in);
		pipex->prev_pipe_in = -1;
	}
	if (pipex->pipefd[1] != -1)
		close(pipex->pipefd[1]);
	if (mini->last_command)
	{
		free(mini->last_command);
		mini->last_command = NULL;
	}
	if (node->cmd_size > 0)
		mini->last_command = ft_strdup(node->cmd[node->cmd_size - 1]);
}

void	create_path(char **s1, char *s2)
{
	char	*new_string;

	new_string = ft_strjoin(*s1, "/");
	free(*s1);
	*s1 = ft_strjoin(new_string, s2);
	free(new_string);
}

void	handle_cmd_error(char **cmd, t_mini *mini, int permission, char *path)
{
	if (!mini->arr_path || mini->arr_path[0] == NULL)
		print_cmd_error(cmd[0], NULL, ": No such file or directory");
	else if (permission)
		print_cmd_error(path, NULL, ": Permission denied");
	else
		print_cmd_error(cmd[0], NULL, ": command not found");
	if (permission)
		mini->exit_code = 126;
	else
		mini->exit_code = 127;
	free(path);
}

void	print_exec_error(t_mini *mini, char **cmd, char *path)
{
	char	*prefix;

	if (path)
		prefix = ft_strjoin(path, ": ");
	else
		prefix = ft_strjoin(cmd[0], ": ");
	print_cmd_error(prefix, NULL, strerror(errno));
	free(prefix);
	mini->exit_code = 126;
}
