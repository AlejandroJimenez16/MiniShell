/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 21:42:30 by alejandj          #+#    #+#             */
/*   Updated: 2025/11/23 22:02:05 by alejandj         ###   ########.fr       */
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

void	expand_vars(t_mini *mini, t_token_info *t_info)
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
		if (mini->cmd[i][0] == '$' && (ft_isalpha(mini->cmd[i][1]) || mini->cmd[i][1] == '_')
			&& t_info[i].type_quote != SINGLE_QUOTES)
		{
			printf("VOY A EXPANDIR\n");
		}
		i++;
	}
}