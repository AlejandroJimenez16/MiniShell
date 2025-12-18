/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:27:28 by alejandj          #+#    #+#             */
/*   Updated: 2025/12/18 01:20:42 by alejandj         ###   ########.fr       */
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

static int	redirect_in(t_cmd *node, t_mini *mini, t_pipex *pipex)
{
	if (node->heredoc == 1)
	{
		pipex->fd_in = here_doc(node->delimeter);
		if (pipex->fd_in < 0)
		{
			print_cmd_error(node->infile, ": Error opening infile");
			mini->exit_code = 1;
			return (1);
		}
		dup2(pipex->fd_in, STDIN_FILENO);
		close(pipex->fd_in);
	}
	else if (node->infile)
	{
		pipex->fd_in = open(node->infile, O_RDONLY);
		if (pipex->fd_in < 0)
		{
			print_cmd_error(node->infile, ": Error opening infile");
			mini->exit_code = 1;
			return (1);
		}
		dup2(pipex->fd_in, STDIN_FILENO);
		close(pipex->fd_in);
	}
	else if (pipex->prev_pipe_in != -1)
	{
		dup2(pipex->prev_pipe_in, STDIN_FILENO);
		close(pipex->prev_pipe_in);
	}
	return (0);
}

static int	redirect_out(t_cmd *node, t_mini *mini, t_pipex *pipex)
{
	if (node->outfile)
	{
		if (node->append)
			pipex->fd_out = open(node->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			pipex->fd_out = open(node->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (pipex->fd_out < 0)
		{
			print_cmd_error(node->outfile, ": Error opening outfile");
			mini->exit_code = 1;
			return (1);
		}
		dup2(pipex->fd_out, STDOUT_FILENO);
		close(pipex->fd_out);
	}
	else if (pipex->pipefd[1] != -1)
	{
		dup2(pipex->pipefd[1], STDOUT_FILENO);
		close(pipex->pipefd[1]);
	}
	return (0);
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
				exit_code = WEXITSTATUS(status); // Terminó normal (exit, return, etc)
			else if (WIFSIGNALED(status))
			{
				// Terminó por una señal (Ctrl+C, Kill, Segfault...)
				exit_code = 128 + WTERMSIG(status);
				// Si fue SIGQUIT (Ctrl+\) hay que imprimir esto según el subject
				if (WTERMSIG(status) == SIGQUIT)
					ft_putendl_fd("Quit (core dumped)", 2);
				// Si fue SIGINT (Ctrl+C) suele quedar bien un salto de línea extra
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
			exec_env_builtins(node->cmd, mini);
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
			}
		}
		pipex.prev_pipe_in = pipex.pipefd[0];
		current = current->next;
	}
	mini->exit_code = wait_for_children(pipex.pid);
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
