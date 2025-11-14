/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 19:40:22 by alejandj          #+#    #+#             */
/*   Updated: 2025/11/14 18:39:04 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	find_var_env(char **env, char *var)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	ft_unset(t_mini *mini)
{
	char	**arr;
	char	*var;
	int		i;

	if (!mini->env || !mini->env[0])
		return ;
	arr = ft_split(mini->line, ' ');
	if (!arr)
		return ;
	i = 1;
	while (arr[i])
	{
		if (arr[i][0] == '"' || arr[i][0] == '\'')
			var = remove_quotes(arr[i], ft_strlen(arr[i]));
		else
			var = ft_strdup(arr[i]);
		if (find_var_env(mini->env, var))
		{
			printf("LA ENCONTRE\n");
		}
		free(var);
		i++;
	}
	ft_free_wa(arr);
}