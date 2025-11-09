/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:11:36 by alejandj          #+#    #+#             */
/*   Updated: 2025/11/09 01:53:53 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini.h"

void	print_full_env(char **env)
{
	t_env	e_env;
	int		i;
	char	**arr;

	i = 0;
	while (env[i] != NULL)
	{
		arr = ft_split(env[i], '=');
		if (!arr)
			return ;
		e_env.var = arr[0];
		e_env.value = arr[1];
		if (e_env.value)
			printf("declare -x %s=\"%s\"\n", e_env.var, e_env.value);
		else
    		printf("declare -x %s\n", e_env.var);
		ft_free_wa(arr);
		i++;
	}
}

char	*manage_has_value(char *var_value, char *eq)
{
	char	*var;
	char	*value;
	char	*value_clean;
	int		len;
	char	*full;

	var = ft_substr(var_value, 0, eq - var_value);
	value = eq + 1;
	len = ft_strlen(value);
	
	// Comprueba si tiene comillas y las quita
	if ((value[0] == '"' || value[0] == '\'') &&
			(value[len - 1] == '"' || value[len - 1] == '\''))
	{
		value_clean = ft_substr(value, 1, len - 2);
		full = malloc(ft_strlen(var) + 1 + ft_strlen(value_clean) + 1);
		ft_strlcpy(full, var, ft_strlen(var) + 1 + ft_strlen(value_clean) + 1);
		ft_strlcat(full, "=", ft_strlen(var) + 1 + ft_strlen(value_clean) + 1);
		ft_strlcat(full, value_clean, ft_strlen(var) + 1 + ft_strlen(value_clean) + 1);
		free(var);
		free(value_clean);
		return (full);
	}
	else
	{
		free(var);
		full = ft_strdup(var_value);
		return (full);
	}
}

void	add_env_vars(char **env, char **arr)
{
	int		i;
	int		j;
	char	*eq;
	char	*full;
	int		found;

	found = 0;
	i = 0;
	while (arr[i] != NULL)
	{
		j = 0;
		while (env[j] != NULL)
		{
			// Si la variable ya existe la actualizo
			if (ft_strncmp(arr[i], env[j], get_len_var(arr[i])) == 0 &&
					get_len_var(arr[i]) == get_len_var(env[j]))
			{
				free(env[j]);
				eq = ft_strchr(arr[i], '=');
				// Si tiene valor
				if (eq)
				{
					full = manage_has_value(arr[i], eq);
					env[j] = full;
					found = 1;
					break ;
				}
				else
				{
					env[j] = ft_strdup(arr[i]);
					found = 1;
					break ;
				}
			}
			j++;
		}
		if (!found)
		{
			// Crear una copia de env y añadir arr[i] al final
		}
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
		add_env_vars(mini->env, arr);
	ft_free_wa(arr);
}
