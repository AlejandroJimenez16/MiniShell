/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:27:28 by alejandj          #+#    #+#             */
/*   Updated: 2025/12/11 22:42:57 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static void	expand_cmd_list(t_list *cmd_list, t_mini *mini, t_token_info *t_info)
{
	t_list	*current;
	t_cmd	*node;

	current = cmd_list;
	while (current)
	{
		node = current->content;
		expand_vars(node->cmd, mini, t_info, node->index_start_cmd);
		current = current->next;
	}
}

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
	if (node->infile)
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

void	execute_commands(t_list *cmd_list, t_mini *mini)
{
	t_list	*current;
	t_cmd	*node;
	t_pipex	pipex;
	
	pipex.prev_pipe_in = -1;
	current = cmd_list;
	while (current)
	{
		node = current->content;
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
		pipex.pid = fork();
		if (pipex.pid < 0)
		{
			ft_putstr_fd("minishell: fork: Error creating process", 2);
			mini->exit_code = 1;
			return ;
		}
		else if (pipex.pid == 0)
		{
			if (redirect_in(node, mini, &pipex))
				exit(mini->exit_code);
			if (redirect_out(node, mini, &pipex))
				exit(mini->exit_code);
			
			// Ejecucion
			
		}
		pipex.prev_pipe_in = pipex.pipefd[0];
		current = current->next;
	}
}

static void	handle_line(t_mini *mini)
{
	char			**tokens;
	t_token_info	*t_info;
	t_list			*cmd_list;

	// Inicializar token_info
	t_info = malloc(count_tokens(mini->line) * sizeof(t_token_info));
	if (!t_info)
		return ;

	// Crear array de tokens
	tokens = split_tokens(mini->line, &t_info);
	if (!tokens)
		return ;

	cmd_list = create_cmd_list(mini->line, tokens, t_info);
	expand_cmd_list(cmd_list, mini, t_info);
	print_cmd_list(cmd_list);
	execute_commands(cmd_list, mini);
}

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;

	if (argc != 1)
		return (ft_putendl_fd("minishell: no args supported", 2), 1);
	(void)argv;
	mini.env = env;
	mini.exit_code = 0;
	mini.last_command = NULL;
	while (1)
	{
		mini.prompt = get_prompt(mini.env);
		mini.line = readline(mini.prompt);
		if (!mini.line)
			return (ft_printf("exit\n"), 0);
		add_history(mini.line);
		handle_line(&mini);
		free(mini.line);
	}
	free(mini.prompt);
	return (0);
}
