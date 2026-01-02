/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 13:38:34 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/02 14:35:21 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

size_t	get_len_var(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	return (i);
}

char	**get_path_cmd(char **env)
{
	int		i;
	char	**arr_path;

	if (!env)
		return (NULL);
	i = 0;
	arr_path = NULL;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			arr_path = ft_split(env[i] + 5, ':');
			break ;
		}
		i++;
	}
	return (arr_path);
}

char	**copy_env(char **env)
{
	int		i;
	int		num_vars;
	char	**new_env;

	num_vars = 0;
	while (env[num_vars] != NULL)
		num_vars++;
	new_env = malloc((num_vars + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

char	**dup_env_add(char **env, int *i)
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
