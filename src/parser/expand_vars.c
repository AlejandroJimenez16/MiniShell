/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 21:42:30 by alejandj          #+#    #+#             */
/*   Updated: 2025/11/22 22:36:20 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

/*
static char	*is_exit_status_code(int exit_code)
{
	char	*num;

	num = ft_itoa(exit_code);
	
}
*/

void	expand_vars(t_mini *mini)
{
	int		i;
	
	i = 0;
	while (mini->cmd[i])
	{
		if (mini->cmd[i][0] == '$' && mini->cmd[i][1] == '?' && mini->cmd[i][2] == '\0')
		{
			free(mini->cmd[i]);
			mini->cmd[i] = ft_itoa(mini->exit_code);
		}
		i++;
	}
}