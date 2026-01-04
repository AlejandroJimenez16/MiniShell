/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:11:36 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/04 21:02:00 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static void	print_full_env(char **env)
{
	int		i;
	char	**arr;
	char	*eq;
	char	**new_env;

	new_env = copy_env(env);
	sort_env(new_env);
	i = 0;
	while (new_env[i] != NULL)
	{
		eq = ft_strchr(new_env[i], '=');
		arr = ft_split(new_env[i], '=');
		if (!arr)
		{
			ft_free_wa(new_env);
			return ;
		}
		if (arr[1])
			printf("declare -x %s=\"%s\"\n", arr[0], arr[1]);
		else if (!arr[1] && eq)
			printf("declare -x %s=\"\"\n", arr[0]);
		else
			printf("declare -x %s\n", arr[0]);
		ft_free_wa(arr);
		i++;
	}
	ft_free_wa(new_env);
}

static int	validate_vars(char *var, char *value)
{
	int	i;

	if (!var || var[0] == '\0')
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
	if (value && (value[0] == '='))
		return (0);
	return (1);
}

static void	split_var_value(char *var_value, char **var, char **value)
{
	char	*eq;
	char	*temp;

	eq = ft_strchr(var_value, '=');
	if (eq)
	{
		*var = ft_substr(var_value, 0, eq - var_value);
		*value = ft_strdup(eq + 1);
		if ((*value[0] == '"' && *value[ft_strlen(*value) - 1] == '"')
			|| (*value[0] == '\'' && *value[ft_strlen(*value) - 1] == '\''))
		{
			temp = remove_quotes(*value, ft_strlen(*value));
			free(*value);
			*value = temp;
		}
	}
	else
	{
		*var = ft_strdup(var_value);
		*value = NULL;
	}
}

static void	manage_env_vars(t_mini *mini, char *var_value)
{
	char	*var;
	char	*value;

	split_var_value(var_value, &var, &value);
	if (!var)
		return ;
	if (!validate_vars(var, value))
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(var_value, 2);
		ft_putendl_fd("': not a valid identifier", 2);
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
