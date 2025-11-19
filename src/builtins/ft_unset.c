/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 19:40:22 by alejandj          #+#    #+#             */
/*   Updated: 2025/11/19 17:02:20 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	find_var_env(char **env, char *var)
{
	int	i;
	int	len;

	len = ft_strlen(var);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0
			&& (env[i][len] == '=' || env[i][len] == '\0'))
			return (1);
		i++;
	}
	return (0);
}

char	**init_new_env(char **env)
{
	int		num_vars;
	char	**new_env;

	num_vars = 0;
	while (env[num_vars])
		num_vars++;
	new_env = malloc((num_vars) * sizeof(char *));
	if (!new_env)
		return (NULL);
	return (new_env);
}

char	**build_new_env(char **env, char *var)
{
	char	**new_env;
	int		i;
	int		j;
	int		len;

	new_env = init_new_env(env);
	len = ft_strlen(var);
	i = 0;
	j = 0;
	while (env[i])
	{
		if (!(ft_strncmp(env[i], var, len) == 0
				&& (env[i][len] == '=' || env[i][len] == '\0')))
		{
			new_env[j] = ft_strdup(env[i]);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

void	unset_var(t_mini *mini, char *var)
{
	char	**old_env;

	if (!find_var_env(mini->env, var))
		return ;
	old_env = mini->env;
	mini->env = build_new_env(mini->env, var);
	ft_free_wa(old_env);
}

void	ft_unset(t_mini *mini)
{
	char	*var;
	int		i;

	if (!mini->env || !mini->env[0])
		return ;
	i = 1;
	while (mini->cmd[i])
	{
		var = remove_quotes(mini->cmd[i], ft_strlen(mini->cmd[i]));
		if (var)
		{
			if (!ft_strchr(var, '='))
				unset_var(mini, var);
			free(var);
		}
		i++;
	}
}
