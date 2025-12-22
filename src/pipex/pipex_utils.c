/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:10:08 by alejandj          #+#    #+#             */
/*   Updated: 2025/12/22 21:59:52 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void	init_pipex(t_pipex *pipex)
{
	pipex->pipefd[0] = -1;
	pipex->pipefd[1] = -1;
	pipex->fd_in = -1;
	pipex->fd_out = -1;
	pipex->pid = -1;
}

int	create_pipe(t_pipex *pipex, t_mini *mini)
{
	if (pipe(pipex->pipefd) != 0)
	{
		ft_putendl_fd("minishell: pipe: Error creating pipe", 2);
		mini->exit_code = 1;
		return (1);
	}
	return (0);
}
