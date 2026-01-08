/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 12:19:37 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/08 13:24:49 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	handle_exit_code_copy(t_mini *mini, char *result, int *i)
{
	char	*exit_code;
	int		index;

	exit_code = ft_itoa(mini->exit_code);
	ft_memcpy(result, exit_code, ft_strlen(exit_code));
	index = ft_strlen(exit_code);
	*i += 2;
	free(exit_code);
	return (index);
}

int	handle_last_command_copy(t_mini *mini, char *result, int *i)
{
	char	*last_command;
	int		index;

	last_command = mini->last_command;
	if (!mini->last_command)
	{
		*i += 2;
		return (0);
	}
	ft_memcpy(result, last_command, ft_strlen(last_command));
	index = ft_strlen(last_command);
	*i += 2;
	return (index);
}

int	handle_env_var_copy(t_mini *mini, char *arg, int *i, char *result)
{
	char	*var;
	char	*value;
	int		j;
	int		index;

	var = ft_substr(arg, *i + 1, get_len_expand_var(arg + *i + 1));
	value = ft_strdup("");
	j = -1;
	while (mini->env[++j])
	{
		if (ft_strncmp(mini->env[j], var, ft_strlen(var)) == 0
			&& (ft_strlen(var) == get_len_var(mini->env[j])))
		{
			free(value);
			value = get_env_value(mini->env[j]);
			break ;
		}
	}
	ft_memcpy(result, value, ft_strlen(value));
	index = ft_strlen(value);
	*i += ft_strlen(var) + 1;
	free(value);
	free(var);
	return (index);
}

int	get_len_expand_var(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
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
