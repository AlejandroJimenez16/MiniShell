/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:34:56 by alejandj          #+#    #+#             */
/*   Updated: 2025/12/29 01:12:13 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	ft_cd(char **cmd, t_mini *mini)
{
	char	cwd[1024];
	char	*path;

	path = cmd[1];
	if (path == NULL)
	{
		path = get_env("HOME", mini->env);
		if (!path)
			return (ft_putendl_fd("minishell: cd: HOME not set", 2),
				mini->exit_code = 1, 1);
	}
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (mini->exit_code = 1, 1);
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("minishell: getcwd");
		mini->exit_code = 1;
		return (1);
	}
	return (0);
}
