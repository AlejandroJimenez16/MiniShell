/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 13:00:08 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/17 19:50:55 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

char	*get_env(char *var, char **env)
{
	int		i;
	char	*eq;

	if (!env || !env[0] || !var)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(var, env[i], ft_strlen(var)) == 0
			&& get_len_var(var) == get_len_var(env[i]))
		{
			eq = ft_strchr(env[i], '=');
			if (eq)
				return (eq + 1);
		}
		i++;
	}
	return (NULL);
}

static char	**dup_env_add(char **env, int *i)
{
	int		num_vars;
	char	**new_env;

	num_vars = 0;
	while (env[num_vars] != NULL)
		num_vars++;
	new_env = malloc((num_vars + 2) * sizeof(char *));
	if (!new_env)
		return (NULL);
	*i = 0;
	while (env[*i])
	{
		new_env[*i] = ft_strdup(env[*i]);
		(*i)++;
	}
	return (new_env);
}

static char	*build_normal_var(char *var, char *value)
{
	char	*full;
	int		full_len;

	full_len = ft_strlen(var) + 1 + ft_strlen(value) + 1;
	full = malloc(full_len);
	if (!full)
		return (NULL);
	ft_strlcpy(full, var, full_len);
	ft_strlcat(full, "=", full_len);
	ft_strlcat(full, value, full_len);
	return (full);
}

static char	**add_var(char *var, char *value, char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = dup_env_add(env, &i);
	if (!new_env)
		return (NULL);
	if (value)
		new_env[i] = build_normal_var(var, value);
	else
		new_env[i] = ft_strdup(var);
	new_env[i + 1] = NULL;
	return (new_env);
}

void	set_env(t_mini *mini, char *var, char *value)
{
	int		i;
	char	**old_env;
	char	**new_env;

	i = 0;
	while (mini->env[i])
	{
		if (ft_strncmp(var, mini->env[i], ft_strlen(var)) == 0
			&& get_len_var(var) == get_len_var(mini->env[i]))
		{
			if (value)
			{
				free(mini->env[i]);
				mini->env[i] = build_normal_var(var, value);
			}
			return ;
		}
		i++;
	}
	old_env = mini->env;
	new_env = add_var(var, value, mini->env);
	if (new_env)
		mini->env = new_env;
	ft_free_wa(old_env);
}
