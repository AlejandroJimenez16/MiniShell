/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 12:39:55 by alejandj          #+#    #+#             */
/*   Updated: 2025/12/13 17:45:43 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static int	is_numeric(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(char **cmd, t_mini *mini)
{
	if (cmd[1] && cmd[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		mini->exit_code = 1;
		return ;
	}
	else if (!cmd[1])
	{
		ft_putendl_fd("exit", 1);
		exit(mini->exit_code);
	}
	else if (cmd[1] && is_numeric(cmd[1]) && !cmd[2])
	{
		ft_putendl_fd("exit", 1);
		exit(ft_atol(cmd[1]));
	}
	else if (cmd[1] && !is_numeric(cmd[1]) && !cmd[2])
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		ft_putendl_fd("exit", 1);
		exit(255);
	}
}
