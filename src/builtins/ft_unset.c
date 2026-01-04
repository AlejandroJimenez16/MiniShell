/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 19:40:22 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/04 21:16:22 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static int	find_var_env(char **env, char *var)
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

static char	**init_new_env(char **env)
{
	int		num_vars;
	char	**new_env;

	num_vars = 0;
	while (env[num_vars])
		num_vars++;
	new_env = malloc(num_vars * sizeof(char *));
	if (!new_env)
		return (NULL);
	return (new_env);
}

static char	**build_new_env(char **env, char *var)
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

void	ft_unset(char **cmd, t_mini *mini)
{
	char	*var;
	int		i;
	char	**old_env;

	i = 1;
	while (cmd[i])
	{
		if ((cmd[i][0] == '"' && cmd[i][ft_strlen(cmd[i]) - 1] == '"')
				|| (cmd[i][0] == '\'' && cmd[i][ft_strlen(cmd[i]) - 1] == '\''))
			var = remove_quotes(cmd[i], ft_strlen(cmd[i]));
		else
			var = ft_strdup(cmd[i]);
		if (var)
		{
			if (!ft_strchr(var, '='))
			{
				if (!find_var_env(mini->env, var))
				{
					i++;
					continue ;
				}
				old_env = mini->env;
				mini->env = build_new_env(mini->env, var);
				ft_free_wa(old_env);
			}
			free(var);
		}
		i++;
	}
}
