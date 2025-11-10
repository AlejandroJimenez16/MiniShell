/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 01:08:20 by alejandj          #+#    #+#             */
/*   Updated: 2025/11/10 19:37:30 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini.h"

int		get_num_vars_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		i++;
	return (i);
}

int		get_len_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break;
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
	ft_strlcat(full, value_clean, ft_strlen(var) + 1 + ft_strlen(value_clean) + 1);
	free(value_clean);
	return (full);
}