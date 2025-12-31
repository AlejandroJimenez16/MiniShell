/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 13:00:08 by alejandj          #+#    #+#             */
/*   Updated: 2025/12/30 22:11:00 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

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

char *build_clean_var(char *var, char *value, int len_value)
{
	char	*value_clean;
	char	*full;
	int		full_size;

	if (!var || !value)
		return (NULL);
	value_clean = remove_quotes(value, len_value);
	full_size = ft_strlen(var) + 1 + ft_strlen(value_clean) + 1;
	full = malloc(full_size);
	if (!full)
	{
		free(value_clean);
		return (NULL);
	}
	ft_strlcpy(full, var, full_size);
	ft_strlcat(full, "=", full_size);
	ft_strlcat(full, value_clean, full_size);
	free(value_clean);
	return (full);
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

void	set_env(char *var, char *value, char **env)
{
	int		i;

	if (!var)
		return ;
	if (!value)
		value = "";	
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(var, env[i], ft_strlen(var)) == 0
		&& get_len_var(var) == get_len_var(env[i]))
		{
			if (value)
			{
				free(env[i]);
				if ((value[0] == '"' && value[ft_strlen(value)-1] == '"')
					|| (value[0] == '\'' && value[ft_strlen(value)-1] == '\''))
					env[i] = build_clean_var(var, value, ft_strlen(value));
				else
					env[i] = build_normal_var(var, value);
			}
			return ;
		}
		i++;
	}
	// Añadir variable
}	
