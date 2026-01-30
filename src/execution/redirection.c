/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 11:46:22 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/30 12:48:59 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static void	check_errno_error(t_redir *redir, t_mini *mini)
{
	if (errno == ENOENT)
		print_cmd_error(redir->file, NULL, ": No such file or directory");
	else if (errno == EACCES)
		print_cmd_error(redir->file, NULL, ": Permission denied");
	else
		perror(redir->file);
	mini->exit_code = 1;
}

static int	handle_infile(t_redir *redir, int *fd_in, t_mini *mini)
{
	if (*fd_in != -1)
		close(*fd_in);
	if (redir->type == HEREDOC)
	{
		*fd_in = here_doc(mini, redir->file, redir->quote);
		if (*fd_in == -1)
		{
			if (g_sig_status == 130)
				mini->exit_code = 130;
			else
				mini->exit_code = 1;
			return (1);
		}
	}
	else
	{
		*fd_in = open(redir->file, O_RDONLY);
		if (*fd_in < 0)
		{
			check_errno_error(redir, mini);
			return (1);
		}
	}
	return (0);
}

static int	handle_outfile(t_redir *redir, int *fd_out, t_mini *mini)
{
	if (*fd_out != -1)
		close(*fd_out);
	if (redir->type == REDIR_APPEND)
		*fd_out = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		*fd_out = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd_out < 0)
	{
		check_errno_error(redir, mini);
		return (1);
	}
	return (0);
}

static void	handle_dup2(int *fd_in, int *fd_out, t_pipex *pipex)
{
	if (*fd_in != -1)
	{
		dup2(*fd_in, STDIN_FILENO);
		close(*fd_in);
	}
	else if (pipex->prev_pipe_in != -1)
	{
		dup2(pipex->prev_pipe_in, STDIN_FILENO);
		close(pipex->prev_pipe_in);
		pipex->prev_pipe_in = -1;
	}
	if (*fd_out != -1)
	{
		dup2(*fd_out, STDOUT_FILENO);
		close(*fd_out);
	}
	else if (pipex->pipefd[1] != -1)
	{
		dup2(pipex->pipefd[1], STDOUT_FILENO);
		close(pipex->pipefd[1]);
		pipex->pipefd[1] = -1;
	}
}

int	handle_redirections(t_cmd *node, t_pipex *pipex, t_mini *mini)
{
	t_list	*current;
	t_redir	*redir;
	int		fd_in;
	int		fd_out;

	fd_in = -1;
	fd_out = -1;
	current = node->redirs;
	while (current)
	{
		redir = (t_redir *)current->content;
		if (redir->type == REDIR_IN || redir->type == HEREDOC)
		{
			if (handle_infile(redir, &fd_in, mini))
				return (1);
		}
		else if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
		{
			if (handle_outfile(redir, &fd_out, mini))
				return (1);
		}
		current = current->next;
	}
	handle_dup2(&fd_in, &fd_out, pipex);
	return (0);
}
