/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 12:19:37 by alejandj          #+#    #+#             */
/*   Updated: 2025/11/28 12:37:36 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	get_len_expand_var(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (ft_isalpha(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

char	*get_env_value(char *env_entry)
{
	char	*eq;
	char	*value;

	eq = ft_strchr(env_entry, '=');
	if (eq)
		value = ft_strdup(eq + 1);
	else
		value = ft_strdup("");
	return (value);
}
