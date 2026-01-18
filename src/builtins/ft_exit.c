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

static void	pen_symbols(char *str, int *i, int *sign)
{
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			*sign = -1;
		(*i)++;
	}
}

static int	parse_exit_number(char *str, long long *out)
{
	long long	res;
	int			sign;
	int			i;

	i = 0;
	res = 0;
	sign = 1;
	if (!str || !*str)
		return (0);
	pen_symbols(str, &i, &sign);
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		if (res > (LLONG_MAX - (str[i] - '0')) / 10)
			return (0);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	*out = res * sign;
	return (1);
}

static void	exit_clean(t_mini *mini)
{
	ft_putendl_fd("exit", 1);
	free_mini(mini);
	free(mini->t_info);
	ft_free_wa(mini->tokens);
	ft_lstclear(&mini->cmd_list, free_cmd_node);
}

void	ft_exit(char **cmd, t_mini *mini)
{
	long long	exit_num;

	if (cmd[1] && cmd[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		mini->exit_code = 1;
		return ;
	}
	if (!cmd[1])
	{
		exit_clean(mini);
		exit(mini->exit_code);
	}
	if (!parse_exit_number(cmd[1], &exit_num))
	{
		ft_putendl_fd("exit", 1);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		mini->exit_code = 255;
		return ;
	}
	exit_clean(mini);
	exit((unsigned char)exit_num);
}
