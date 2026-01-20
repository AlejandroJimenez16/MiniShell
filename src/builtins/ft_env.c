/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:07:26 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/20 13:02:42 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void	ft_env(t_mini *mini, char **cmd, char **env)
{
	int		i;

	if (!env || !env[0])
		return ;
	if (cmd[1])
	{
		print_cmd_error("env: ", NULL, "arguments not allowed");
		mini->exit_code = 1;
		return ;
	}
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strchr(env[i], '='))
			printf("%s\n", env[i]);
		i++;
	}
}
