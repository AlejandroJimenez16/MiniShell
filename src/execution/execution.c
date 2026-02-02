/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:38:17 by alejandj          #+#    #+#             */
/*   Updated: 2026/02/02 16:09:17 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static int	get_exit_code(int status)
{
	int	exit_code;

	exit_code = 0;
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		exit_code = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", 2);
	}
	return (exit_code);
}

static int	wait_for_children(pid_t last_pid)
{
	pid_t	pid;
	int		status;
	int		exit_code;
	int		sig_int;

	exit_code = 0;
	sig_int = 0;
	pid = wait(&status);
	while (pid > 0)
	{
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT && !sig_int)
		{
			sig_int = 1;
			write(1, "\n", 1);
		}
		if (pid == last_pid)
			exit_code = get_exit_code(status);
		pid = wait(&status);
	}
	return (exit_code);
}

static int	manage_execution(t_cmd *node, t_pipex *pipex,
		t_mini *mini, t_list *current)
{
	int	status;

	if (is_builtin(node->cmd) && pipex->prev_pipe_in == -1
		&& !current->next)
		return (exec_env_builtins_parent(node, mini, pipex));
	pipex->pid = fork();
	signal(SIGINT, SIG_IGN);
	if (pipex->pid < 0)
	{
		close_pipex_error(pipex);
		return (ft_putstr_fd("minishell: fork: Error creating process", 2), 1);
	}
	else if (pipex->pid == 0)
	{
		status = handle_child(node, mini, pipex);
		clean_all(mini);
		exit(status);
	}
	else
		handle_parent(pipex, mini, node);
	return (0);
}

static int	process_command(t_mini *mini, t_pipex *pipex, pid_t	*last_pid)
{
	t_list	*current;
	t_cmd	*node;

	current = mini->cmd_list;
	while (current)
	{
		node = current->content;
		init_pipex(pipex);
		if (current->next && create_pipe(pipex))
		{
			if (pipex->prev_pipe_in != -1)
			{
				close(pipex->prev_pipe_in);
				pipex->prev_pipe_in = -1;
			}
			return (1);
		}
		if (manage_execution(node, pipex, mini, current))
			return (1);
		if (pipex->pid != -1)
			*last_pid = pipex->pid;
		pipex->prev_pipe_in = pipex->pipefd[0];
		current = current->next;
	}
	return (0);
}

void	execute_commands(t_mini *mini)
{
	t_pipex	pipex;
	pid_t	last_pid;
	int		ret;
	int		status;

	pipex.prev_pipe_in = -1;
	last_pid = -1;
	ret = process_command(mini, &pipex, &last_pid);
	if (pipex.prev_pipe_in != -1)
		close(pipex.prev_pipe_in);
	if (last_pid != -1)
	{
		status = wait_for_children(last_pid);
		if (ret)
			mini->exit_code = 1;
		else
			mini->exit_code = status;
	}
	init_signals();
}
