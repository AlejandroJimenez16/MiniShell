/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:38:17 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/16 19:58:29 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	wait_for_children(pid_t last_pid)
{
	pid_t	pid;
	int		status;
	int		exit_code;

	exit_code = 0;
	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				exit_code = 128 + WTERMSIG(status);
				if (WTERMSIG(status) == SIGQUIT)
					ft_putendl_fd("Quit (core dumped)", 2);
				if (WTERMSIG(status) == SIGINT)
					write(1, "\n", 1);
			}
		}
		pid = wait(&status);
	}
	return (exit_code);
}

static int	handle_child(t_cmd *node, t_mini *mini, t_pipex *pipex)
{
	setup_child_signals();
	if (handle_redirections(node, pipex, mini))
		return (mini->exit_code);
	if (is_builtin(node->cmd))
		return (exec_builtins(node->cmd, mini));
	else
		execute_simple_commands(node->cmd, mini);
	return (mini->exit_code);
}

static void	handle_parent(t_pipex *pipex, t_mini *mini, t_cmd *node)
{
	if (pipex->prev_pipe_in != -1)
		close(pipex->prev_pipe_in);
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

static int	manage_execution(t_cmd *node, t_pipex *pipex,
		t_mini *mini, t_list *current)
{
	int	status;
	if (is_env_builtin(node->cmd) && pipex->prev_pipe_in == -1
		&& !current->next)
		return (exec_env_builtins_parent(node, mini, pipex));
	pipex->pid = fork();
	signal(SIGINT, SIG_IGN);
	if (pipex->pid < 0)
		return (ft_putstr_fd("minishell: fork: Error creating process", 2),
			mini->exit_code = 1, 1);
	else if (pipex->pid == 0)
	{
		status = handle_child(node, mini, pipex);
		free(mini->last_command);
		free(mini->t_info);
		ft_free_wa(mini->tokens);
		ft_lstclear(&mini->cmd_list, free_cmd_node);
		ft_free_wa(mini->env);
		rl_clear_history();
		exit(status);	
	}
	else
		handle_parent(pipex, mini, node);
	return (0);
}

void	execute_commands(t_list *cmd_list, t_mini *mini)
{
	t_list	*current;
	t_cmd	*node;
	t_pipex	pipex;
	pid_t	last_pid;

	pipex.prev_pipe_in = -1;
	last_pid = -1;
	current = cmd_list;
	while (current)
	{
		node = current->content;
		init_pipex(&pipex);
		if (current->next && create_pipe(&pipex, mini))
			return ;
		if (manage_execution(node, &pipex, mini, current))
			return ;
		if (pipex.pid != -1)
			last_pid = pipex.pid;
		pipex.prev_pipe_in = pipex.pipefd[0];
		current = current->next;
	}
	if (last_pid != -1)
		mini->exit_code = wait_for_children(last_pid);
	init_signals();
}
