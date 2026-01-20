/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:11:36 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/20 13:01:28 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static void	split_var_value(char *var_value, char **var, char **value)
{
	char	*eq;

	eq = ft_strchr(var_value, '=');
	if (eq)
	{
		*var = ft_substr(var_value, 0, eq - var_value);
		*value = ft_strdup(eq + 1);
	}
	else
	{
		*var = ft_strdup(var_value);
		*value = NULL;
	}
}

static void	print_full_env(char **env)
{
	int		i;
	char	*var;
	char	*value;
	char	**new_env;

	new_env = copy_env(env);
	sort_env(new_env);
	i = 0;
	while (new_env[i] != NULL)
	{
		split_var_value(new_env[i], &var, &value);
		if (value)
			printf("declare -x %s=\"%s\"\n", var, value);
		else
			printf("declare -x %s\n", var);
		free(var);
		if (value)
			free(value);
		i++;
	}
	ft_free_wa(new_env);
}

static int	validate_vars(char *var)
{
	int	i;

	if (!var || !var[0])
		return (0);
	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (0);
	i = 1;
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	manage_env_vars(t_mini *mini, char *var_value)
{
	char	*var;
	char	*value;
	char	*temp;

	split_var_value(var_value, &var, &value);
	if (!var)
		return ;
	if (value && ((value[0] == '"' && value[ft_strlen(value) - 1] == '"')
		|| (value[0] == '\'' && value[ft_strlen(value) - 1] == '\'')))
	{
		temp = remove_quotes(value, ft_strlen(value));
		free(value);
		value = temp;
	}
	if (!validate_vars(var))
	{
		print_cmd_error("export: ", var_value, "not a valid identifier");
		mini->exit_code = 1;
	}
	else
		set_env(mini, var, value);
	free(var);
	if (value)
		free(value);
}

void	ft_export(char **cmd, t_mini *mini)
{
	int		i;

	if (!cmd[1])
	{
		print_full_env(mini->env);
		return ;
	}
	i = 1;
	while (cmd[i])
	{
		manage_env_vars(mini, cmd[i]);
		i++;
	}
}
