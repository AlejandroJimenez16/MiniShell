/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 11:46:22 by alejandj          #+#    #+#             */
/*   Updated: 2025/12/18 11:48:35 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static int	check_infile_permissions(char *file, t_mini *mini)
{
	if (access(file, F_OK) != 0)
	{
		print_cmd_error(file, ": No such file or directory");
		mini->exit_code = 127;
		return (1);
	}
	if (access(file, R_OK) != 0)
	{
		print_cmd_error(file, ": Permission denied");
		mini->exit_code = 126;
		return (1);
	}
	return (0);
}

static int	check_outfile_permissions(char *file, t_mini *mini)
{
	if (access(file, F_OK) == 0 && access(file, W_OK) != 0)
	{
		print_cmd_error(file, ": Permission denied");
		mini->exit_code = 126;
		return (1);
	}
	return (0);
}

static void	redirect_prev_pipe_in(t_pipex *pipex)
{
	dup2(pipex->prev_pipe_in, STDIN_FILENO);
	close(pipex->prev_pipe_in);
}

int	redirect_in(t_cmd *node, t_mini *mini, t_pipex *pipex)
{
	if (node->heredoc == 1)
	{
		pipex->fd_in = here_doc(node->delimeter);
		if (pipex->fd_in < 0)
			return (print_cmd_error(node->infile, ": Error opening infile"),
				mini->exit_code = 1, mini->exit_code);
		dup2(pipex->fd_in, STDIN_FILENO);
		close(pipex->fd_in);
	}
	else if (node->infile)
	{
		if (check_infile_permissions(node->infile, mini))
			return (mini->exit_code);
		pipex->fd_in = open(node->infile, O_RDONLY);
		if (pipex->fd_in < 0)
			return (print_cmd_error(node->infile, ": Error opening infile"),
				mini->exit_code = 1, mini->exit_code);
		dup2(pipex->fd_in, STDIN_FILENO);
		close(pipex->fd_in);
	}
	else if (pipex->prev_pipe_in != -1)
		redirect_prev_pipe_in(pipex);
	return (0);
}

int	redirect_out(t_cmd *node, t_mini *mini, t_pipex *pipex)
{
	if (node->outfile)
	{
		if (check_outfile_permissions(node->outfile, mini))
			return (mini->exit_code);
		if (node->append)
			pipex->fd_out = open(node->outfile, O_CREAT | O_WRONLY
					| O_APPEND, 0644);
		else
			pipex->fd_out = open(node->outfile, O_CREAT | O_WRONLY
					| O_TRUNC, 0644);
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
