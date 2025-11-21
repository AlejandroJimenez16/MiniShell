/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 18:01:10 by alejandj          #+#    #+#             */
/*   Updated: 2025/11/21 18:19:11 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	is_builtin(char **cmd)
{
	if (!cmd || !cmd[0])
		return (0);
	if (ft_strncmp(cmd[0], "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "cd", 3) == 0)
		return (1);	
	else if (ft_strncmp(cmd[0], "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "export", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "env", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "exit", 4) == 0)
		return (1);
	return (0);	
}

void	exec_builtins(t_mini *mini)
{
	if (ft_strncmp(mini->cmd[0], "echo", 4) == 0)
		ft_echo(mini->cmd);
	else if (ft_strncmp(mini->cmd[0], "cd", 3) == 0)
		ft_cd(mini);
	else if (ft_strncmp(mini->cmd[0], "pwd", 3) == 0)
		ft_pwd(mini);
	else if (ft_strncmp(mini->cmd[0], "export", 6) == 0)
		ft_export(mini);
	else if (ft_strncmp(mini->cmd[0], "unset", 5) == 0)
		ft_unset(mini);
	else if (ft_strncmp(mini->cmd[0], "env", 3) == 0)
		ft_env(mini->env);
	else if (ft_strncmp(mini->cmd[0], "exit", 4) == 0)
		ft_exit(mini);
}