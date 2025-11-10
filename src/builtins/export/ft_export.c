/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:11:36 by alejandj          #+#    #+#             */
/*   Updated: 2025/11/10 20:11:26 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini.h"

void	print_full_env(char **env)
{
	t_env	e_env;
	int		i;
	char	**arr;
	char	*eq;

	i = 0;
	while (env[i] != NULL)
	{
		eq = ft_strchr(env[i], '=');
		arr = ft_split(env[i], '=');
		if (!arr)
			return ;
		e_env.var = arr[0];
		e_env.value = arr[1];
		if (e_env.value)
			printf("declare -x %s=\"%s\"\n", e_env.var, e_env.value);
		else if (!e_env.value && eq)
    		printf("declare -x %s=\"\"\n", e_env.var);
		else
			printf("declare -x %s\n", e_env.var);
		ft_free_wa(arr);
		i++;
	}
}

char	**add_env_var(char **env, char *var_value, char *eq)
{
	t_env	e_env;
	int		num_vars;
	int		i;
	char	**new_env;
	int		len;
	
	if (eq)
	{
		e_env.var = ft_substr(var_value, 0, eq - var_value);
		e_env.value = eq + 1;
		len = ft_strlen(e_env.value);	
	}
	else
    {
        e_env.var = ft_strdup(var_value);
        e_env.value = NULL;
        len = 0;
    }
	num_vars = 0;
	while (env[num_vars] != NULL)
		num_vars++;
	new_env = malloc((num_vars + 2) * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	if (e_env.value && ((e_env.value[0] == '"' || e_env.value[0] == '\'') &&
            (e_env.value[len - 1] == '"' || e_env.value[len - 1] == '\'') ))
	{
		new_env[i] = build_clean_var(e_env.var, e_env.value, len);
	}
	else if (eq)
		new_env[i] = ft_strdup(var_value);
	else
		new_env[i] = ft_strdup(e_env.var);
	free(e_env.var);
	new_env[i + 1] = NULL;
	return (new_env);
}

char	*manage_has_value(char *var_value, char *eq)
{
	t_env	e_env;
	int		len;

	e_env.var = ft_substr(var_value, 0, eq - var_value);
	e_env.value = eq + 1;
	len = ft_strlen(e_env.value);
	
	// Comprueba si tiene comillas y las quita
	if ((e_env.value[0] == '"' || e_env.value[0] == '\'') &&
			(e_env.value[len - 1] == '"' || e_env.value[len - 1] == '\''))
	{
		e_env.full = build_clean_var(e_env.var, e_env.value, len);
		return (e_env.full);
	}
	else
	{
		free(e_env.var);
		e_env.full = ft_strdup(var_value);
		return (e_env.full);
	}
}

void	manage_env_vars(t_mini *mini, char **arr)
{
	int		i;
	int		j;
	char	*eq;
	char	*full;
	int		found;

	i = 0;
	while (arr[i] != NULL)
	{
		found = 0;
		j = 0;
		eq = ft_strchr(arr[i], '=');
		while (mini->env[j] != NULL)
		{
			// Si la variable ya existe la actualizo
			if (ft_strncmp(arr[i], mini->env[j], get_len_var(arr[i])) == 0 &&
					get_len_var(arr[i]) == get_len_var(mini->env[j]))
			{
				// Si tiene valor
				if (eq)
				{
					free(mini->env[j]);
					full = manage_has_value(arr[i], eq);
					mini->env[j] = full;
				}
				found = 1;
				break ;
			}
			j++;
		}
		if (!found)
			mini->env = add_env_var(mini->env, arr[i], eq);
		i++;
	}
}

void	ft_export(t_mini *mini)
{
	char	**arr;
	
	if (!mini->env || !mini->env[0])
		return ;
	arr = ft_split(mini->line, ' ');
	if (!arr)
		return ;
	if (arr[1] == NULL)
		print_full_env(mini->env);
	else
		manage_env_vars(mini, arr + 1);
	ft_free_wa(arr);
}
