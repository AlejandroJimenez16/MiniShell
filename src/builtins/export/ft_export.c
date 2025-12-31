/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:11:36 by alejandj          #+#    #+#             */
/*   Updated: 2025/12/30 22:00:14 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini.h"

char	**add_env_var(char **env, char *var_value, char *eq)
{
	t_env	e_env;
	int		i;
	char	**new_env;
	int		len;

	new_env = dup_env(env, &i);
	if (eq)
	{
		e_env.var = ft_substr(var_value, 0, eq - var_value);
		e_env.value = eq + 1;
		len = ft_strlen(e_env.value);
		if (e_env.value && (e_env.value[0] == '"' || e_env.value[0] == '\''))
			new_env[i] = build_clean_var(e_env.var, e_env.value, len);
		else
			new_env[i] = ft_strdup(var_value);
	}
	else
	{
		e_env.var = ft_strdup(var_value);
		e_env.value = NULL;
		new_env[i] = ft_strdup(e_env.var);
	}
	return (free(e_env.var), new_env[i + 1] = NULL, new_env);
}

int	update_var(char **env, char *var, char *eq)
{
	int		j;
	char	*full;

	j = 0;
	while (env[j] != NULL)
	{
		if (ft_strncmp(var, env[j], get_len_var(var)) == 0
			&& get_len_var(var) == get_len_var(env[j]))
		{
			if (eq)
			{
				free(env[j]);
				full = manage_has_value(var, eq);
				env[j] = full;
			}
			return (1);
		}
		j++;
	}
	return (0);
}

void	manage_env_vars(t_mini *mini, char *var_value)
{
	char	*eq;
	int		found;

	found = 0;
	eq = ft_strchr(var_value, '=');

	// CAMBIAR POR SET_ENV
	//----------------------
	if (update_var(mini->env, var_value, eq))
		found = 1;
	if (!found)
		mini->env = add_env_var(mini->env, var_value, eq);
	//----------------------
}

void	process_export_var(t_mini *mini, char *var_value)
{
	if (!parse_export(var_value))
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(var_value, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		mini->exit_code = 1;
	}
	else
		manage_env_vars(mini, var_value);
}

void	ft_export(char **cmd, t_mini *mini)
{
	int		i;

	if (!mini->env || !mini->env[0])
		return ;
	if (!cmd[1])
	{
		print_full_env(mini->env);
		return ;
	}
	i = 1;
	while (cmd[i])
	{
		process_export_var(mini, cmd[i]);
		i++;
	}
}
