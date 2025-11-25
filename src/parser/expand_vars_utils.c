/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:30:00 by alejandj          #+#    #+#             */
/*   Updated: 2025/11/25 21:10:26 by alejandj         ###   ########.fr       */
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

static int	handle_exit_code_len(t_mini *mini, int *i)
{
	char	*exit_code;
	int		count;

	count = 0;
	exit_code = ft_itoa(mini->exit_code);
	count = ft_strlen(exit_code);
	free(exit_code);
	*i += 2;
	return (count);
}

static	int	handle_env_var_len(t_mini *mini, char *arg, int *i)
{
	char	*var;
	int		j;
	char	*eq;
	int		count;

	count = 0;
	var = ft_substr(arg, *i + 1, get_len_expand_var(arg + *i + 1));
	j = 0;
	while (mini->env[j])
	{
		if (ft_strncmp(mini->env[j], var, ft_strlen(var)) == 0
			&& (ft_strlen(var) == get_len_var(mini->env[j])))
		{
			eq = ft_strchr(mini->env[j], '=');
			if (eq)
				count += ft_strlen(eq + 1);
			else
				count += 0;
			break ;
		}
		j++;
	}
	*i += ft_strlen(var) + 1;
	free(var);
	return (count);
}

int	get_len_token(t_mini *mini, char *arg)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i + 1] == '?')
			count += handle_exit_code_len(mini, &i);
		else if (arg[i] == '$' && (ft_isalpha(arg[i + 1]) || arg[i + 1] == '_'))
			count += handle_env_var_len(mini, arg, &i);
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}
