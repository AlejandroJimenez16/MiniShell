/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:27:28 by alejandj          #+#    #+#             */
/*   Updated: 2025/12/18 13:21:15 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static void	init_pipex(t_pipex *pipex)
{
	pipex->pipefd[0] = -1;
	pipex->pipefd[1] = -1;
	pipex->fd_in = -1;
	pipex->fd_out = -1;
	pipex->pid = -1;
}

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

void	execute_commands(t_list *cmd_list, t_mini *mini, t_token_info *t_info)
{
	t_list	*current;
	t_cmd	*node;
	t_pipex	pipex;
	
	pipex.prev_pipe_in = -1;
	current = cmd_list;
	while (current)
	{
		node = current->content;
		expand_vars(node->cmd, mini, t_info, node->index_start_cmd);
		init_pipex(&pipex);
		if (current->next)
		{
			if (pipe(pipex.pipefd) != 0)
			{
				ft_putendl_fd("minishell: pipe: Error creating pipe", 2);
				mini->exit_code = 1;
				return ;
			}
		}
		if (is_env_builtin(node->cmd) && pipex.prev_pipe_in == -1 && !current->next)
		{
			mini->exit_code = exec_env_builtins(node->cmd, mini);
			if (mini->last_command)
				free(mini->last_command);
			if (node->cmd_size > 0)
				mini->last_command = ft_strdup(node->cmd[node->cmd_size - 1]);
		}
		else
		{
			pipex.pid = fork();
			signal(SIGINT, SIG_IGN);
			if (pipex.pid < 0)
			{
				ft_putstr_fd("minishell: fork: Error creating process", 2);
				mini->exit_code = 1;
				return ;
			}
			else if (pipex.pid == 0)
			{
				setup_child_signals();
				if (redirect_in(node, mini, &pipex))
					exit(mini->exit_code);
				if (redirect_out(node, mini, &pipex))
					exit(mini->exit_code);
				if (is_builtin(node->cmd))
					exit(exec_builtins(node->cmd, mini));
				else
					execute_simple_commands(node->cmd, mini);
			}
			else
			{
				if (pipex.prev_pipe_in != -1)
                	close(pipex.prev_pipe_in);
            	if (pipex.pipefd[1] != -1)
                	close(pipex.pipefd[1]);
				if (mini->last_command)
					free(mini->last_command);
				if (node->cmd_size > 0)
					mini->last_command = ft_strdup(node->cmd[node->cmd_size - 1]);
				mini->exit_code = wait_for_children(pipex.pid);
			}
		}
		pipex.prev_pipe_in = pipex.pipefd[0];
		current = current->next;
	}
	init_signals();
}

static void	handle_line(t_mini *mini)
{
	char			**tokens;
	t_token_info	*t_info;
	t_list			*cmd_list;

	t_info = malloc(count_tokens(mini->line) * sizeof(t_token_info));
	if (!t_info)
		return ;
	tokens = split_tokens(mini->line, &t_info);
	if (!tokens)
		return ;
	cmd_list = create_cmd_list(mini->line, tokens, t_info);
	execute_commands(cmd_list, mini, t_info);
}

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;

	if (argc != 1)
		return (ft_putendl_fd("minishell: no args supported", 2), 1);
	(void)argv;
	mini.env = env;
	mini.exit_code = 0;
	mini.last_command = ft_strdup("./minishell");
	init_signals();
	while (1)
	{
		if (g_sig_status != 0)
		{
			mini.exit_code = g_sig_status;
			g_sig_status = 0;
		}
		mini.prompt = get_prompt(mini.env);
		mini.line = readline(mini.prompt);
		if (!mini.line)
			return (ft_printf("exit\n"), 0);
		add_history(mini.line);
		handle_line(&mini);
		free(mini.line);
	}
	return (free(mini.prompt), 0);
}
