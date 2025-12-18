/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 21:42:30 by alejandj          #+#    #+#             */
/*   Updated: 2025/12/18 01:23:43 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static int	handle_exit_code_copy(t_mini *mini, char *result, int *i)
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

static int	handle_last_command_copy(t_mini *mini, char *result, int *i)
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

static int	handle_env_var_copy(t_mini *mini, char *arg, int *i, char *result)
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

static char	*expand_vars_in_token(t_mini *mini, char *arg)
{
	char	*result;
	int		i;
	int		i_result;
	int		len;

	len = get_len_token(mini, arg);
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	i_result = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i + 1] == '?')
			i_result += handle_exit_code_copy(mini, result + i_result, &i);
		else if (arg[i] == '$' && arg[i + 1] == '_'
			&& !(ft_isalnum(arg[i + 2]) || arg[i + 2] == '_'))
			i_result += handle_last_command_copy(mini, result + i_result, &i);
		else if (arg[i] == '$' && (ft_isalpha(arg[i + 1]) || arg[i + 1] == '_'))
			i_result += handle_env_var_copy(mini, arg, &i, result + i_result);
		else
			result[i_result++] = arg[i++];
	}
	result[i_result] = '\0';
	return (result);
}

void	expand_vars(char **cmd, t_mini *mini, t_token_info *t_info, int start)
{
	int		i;
	char	*temp;

	i = 0;
	while (cmd[i])
	{
		if (t_info[start].type_quote != SINGLE_QUOTES)
		{
			temp = cmd[i];
			cmd[i] = expand_vars_in_token(mini, cmd[i]);
			free(temp);
		}
		start++;
		i++;
	}
}
