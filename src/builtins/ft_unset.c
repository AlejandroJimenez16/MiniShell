/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 19:40:22 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/08 19:04:04 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static char	**init_new_env(char **env)
{
	int		num_vars;
	char	**new_env;

	num_vars = 0;
	while (env[num_vars])
		num_vars++;
	new_env = malloc((num_vars + 1) * sizeof(char *));
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
	int		found;

	found = 0;
	new_env = init_new_env(env);
	if (!new_env)
		return (NULL);
	len = ft_strlen(var);
	i = -1;
	j = 0;
	while (env[++i])
	{
		if (ft_strncmp(env[i], var, len) == 0
			&& (env[i][len] == '=' || env[i][len] == '\0'))
			found = 1;
		else
			new_env[j++] = ft_strdup(env[i]);
	}
	new_env[j] = NULL;
	if (!found)
		return (ft_free_wa(new_env), NULL);
	return (new_env);
}

static void	delete_var(char *var, t_mini *mini)
{
	char	**new_env;

	if (!var || ft_strchr(var, '='))
		return ;
	new_env = build_new_env(mini->env, var);
	if (new_env)
	{
		ft_free_wa(mini->env);
		mini->env = new_env;
	}
}

void	ft_unset(char **cmd, t_mini *mini)
{
	char	*var;
	int		i;

	i = 1;
	while (cmd[i])
	{
		if ((cmd[i][0] == '"' && cmd[i][ft_strlen(cmd[i]) - 1] == '"')
				|| (cmd[i][0] == '\'' && cmd[i][ft_strlen(cmd[i]) - 1] == '\''))
			var = remove_quotes(cmd[i], ft_strlen(cmd[i]));
		else
			var = ft_strdup(cmd[i]);
		delete_var(var, mini);
		free(var);
		i++;
	}
}
