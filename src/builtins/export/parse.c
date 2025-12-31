/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:06:05 by alejandj          #+#    #+#             */
/*   Updated: 2025/12/30 19:51:46 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini.h"

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
	if (!validate_vars(v_env.var, v_env.value))
		return (0);
	return (1);
}
