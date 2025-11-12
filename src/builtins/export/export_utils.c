/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 01:08:20 by alejandj          #+#    #+#             */
/*   Updated: 2025/11/12 13:42:51 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini.h"

int	get_len_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	return (i);
}

char	*build_clean_var(char *var, char *value, int len_value)
{
	char	*value_clean;
	char	*full;

	value_clean = ft_substr(value, 1, len_value - 2);
	full = malloc(ft_strlen(var) + 1 + ft_strlen(value_clean) + 1);
	if (!full)
		return (NULL);
	ft_strlcpy(full, var, ft_strlen(var) + 1 + ft_strlen(value_clean) + 1);
	ft_strlcat(full, "=", ft_strlen(var) + 1 + ft_strlen(value_clean) + 1);
	ft_strlcat(full, value_clean,
		ft_strlen(var) + 1 + ft_strlen(value_clean) + 1);
	free(value_clean);
	return (full);
}

void	sort_env(char **cpy_env)
{
	int		i;
	int		sorted;
	int		len;
	char	*temp;

	len = 0;
	while (cpy_env[len])
		len++;
	sorted = 0;
	while (sorted == 0)
	{
		sorted = 1;
		i = 0;
		while (i < len - 1)
		{
			if (ft_strncmp(cpy_env[i], cpy_env[i + 1], 1024) > 0)
			{
				temp = cpy_env[i];
				cpy_env[i] = cpy_env[i + 1];
				cpy_env[i + 1] = temp;
				sorted = 0;
			}
			i++;
		}
	}
}

void	print_full_env(char **env)
{
	int		i;
	char	**arr;
	char	*eq;
	char	**cpy_env;

	cpy_env = dup_env(env, &i);
	cpy_env[i] = NULL;
	sort_env(cpy_env);
	i = 0;
	while (cpy_env[i] != NULL)
	{
		eq = ft_strchr(cpy_env[i], '=');
		arr = ft_split(cpy_env[i], '=');
		if (!arr)
			return ;
		if (arr[1])
			printf("declare -x %s=\"%s\"\n",arr[0], arr[1]);
		else if (!arr[1] && eq)
			printf("declare -x %s=\"\"\n", arr[0]);
		else
			printf("declare -x %s\n", arr[0]);
		ft_free_wa(arr);
		i++;
	}
	ft_free_wa(cpy_env);
}

char	*manage_has_value(char *var_value, char *eq)
{
	t_env	e_env;
	int		len;

	e_env.var = ft_substr(var_value, 0, eq - var_value);
	e_env.value = eq + 1;
	len = ft_strlen(e_env.value);
	if ((e_env.value[0] == '"' || e_env.value[0] == '\'')
		&& (e_env.value[len - 1] == '"' || e_env.value[len - 1] == '\''))
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
