/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 20:06:52 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/14 15:09:53 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	has_n(char *arg)
{
	int	i;

	i = 1;
	if (!arg || arg[0] != '-' || arg[1] == '\0')
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(t_mini *mini, char **cmd)
{
	int	i;
	int	newline;

	mini->exit_code = 0;
	i = 1;
	newline = 1;
	if (!cmd[i])
	{
		printf("\n");
		return ;
	}
	while (cmd[i] && has_n(cmd[i]))
	{
		newline = 0;
		i++;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}
