/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:06:05 by alejandj          #+#    #+#             */
/*   Updated: 2025/11/13 19:31:08 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini.h"

int	count_quotes(char *value)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (value[i])
	{
		if (value[i] == '"' || value[i] == '\'')
			count++;
		i++;
	}
	return (count);
}

char	*remove_quotes(char *value, int len_value)
{
	char	*value_clean;
	int		i;
	int		j;

	i = 0;
	j = 0;
	value_clean = malloc(len_value - count_quotes(value) + 1);
	if (!value_clean)
		return (NULL);
	while (value[i])
	{
		if (value[i] != '"' && value[i] != '\'')
		{
			value_clean[j] = value[i];
			j++;
		}
		i++;
	}
	value_clean[j] = '\0';
	return (value_clean);
}

char	*build_clean_var(char *var, char *value, int len_value)
{
	char	*value_clean;
	char	*full;
	int		full_len;

	if (!var || !value)
		return (NULL);
	value_clean = remove_quotes(value, len_value);
	full = malloc(ft_strlen(var) + 1 + ft_strlen(value_clean) + 1);
	if (!full)
	{
		free(value_clean);
		return (NULL);
	}
	full_len = ft_strlen(var) + 1 + ft_strlen(value_clean) + 1;
	ft_strlcpy(full, var, full_len);
	ft_strlcat(full, "=", full_len);
	ft_strlcat(full, value_clean, full_len);
	free(value_clean);
	return (full);
}

int	parse_export(char *var_value)
{
	t_env	v_env;
	char	*eq;

	if (!var_value)
		return (1);
	eq = ft_strchr(var_value, '=');
	if (eq)
	{
		v_env.var = ft_substr(var_value, 0, eq - var_value);
		v_env.value = eq + 1;
	}
	else
	{
		v_env.var = ft_strdup(var_value);
		v_env.value = NULL;
	}
	if (!v_env.var || v_env.var[0] == '\0')
		return (0);
	if (!ft_isalpha(v_env.var[0]) && v_env.var[0] != '_')
		return (0);
	if (v_env.value && (v_env.value[0] == '='))
		return (0);
	return (1);
}
