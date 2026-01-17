/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 12:39:55 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/17 21:16:09 by alejandj         ###   ########.fr       */
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
	int	exit_num;
	
	if (cmd[1] && cmd[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		mini->exit_code = 1;
		return ;
	}
	else if (!cmd[1])
	{
		ft_putendl_fd("exit", 1);
		free_mini(mini);
		free(mini->t_info);
		ft_free_wa(mini->tokens);
		ft_lstclear(&mini->cmd_list, free_cmd_node);
		exit(mini->exit_code);
	}
	else if (cmd[1] && is_numeric(cmd[1]) && !cmd[2])
	{
		exit_num = ft_atoi(cmd[1]);
		ft_putendl_fd("exit", 1);
		free_mini(mini);
		free(mini->t_info);
		ft_free_wa(mini->tokens);
		ft_lstclear(&mini->cmd_list, free_cmd_node);
		exit(exit_num);
	}
	else if (cmd[1] && !is_numeric(cmd[1]) && !cmd[2])
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		ft_putendl_fd("exit", 1);
		free_mini(mini);
		free(mini->t_info);
		ft_free_wa(mini->tokens);
		ft_lstclear(&mini->cmd_list, free_cmd_node);
		exit(255);
	}
}
