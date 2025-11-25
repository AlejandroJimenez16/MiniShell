/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 21:42:30 by alejandj          #+#    #+#             */
/*   Updated: 2025/11/25 20:08:48 by alejandj         ###   ########.fr       */
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

static int	get_len_token(t_mini *mini, char *arg)
{
	int		i;
	int		count;
	char	*var;
	int		j;
	char	*eq;
	
	i = 0;
	count = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
		{
			if (arg[i + 1] == '?')
			{
				char *exit_code = ft_itoa(mini->exit_code);
				count += ft_strlen(exit_code);
				free(exit_code);
				i += 2;
				continue ;
			}
			if (ft_isalpha(arg[i + 1]) || arg[i + 1] == '_')
			{
				var = ft_substr(arg, i + 1, get_len_expand_var(arg + i + 1));
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
				i += ft_strlen(var) + 1;
				free(var);
				continue ;
			}
			count++;
    		i++;
    		continue;
		}
		else
		{
			count++;
			i++;	
		}
	}
	return (count);
}

static char	*expand_vars_in_token(t_mini *mini, char *arg)
{
	char	*result;
	int		i;
	int		i_result;
	int		len;
	int		j;
	char	*value;
	char	*eq;

	len = get_len_token(mini, arg);
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	i_result = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
		{
			if (arg[i + 1] == '?')
			{
				char *exit_code = ft_itoa(mini->exit_code);
				ft_memcpy(result + i_result, exit_code, ft_strlen(exit_code));
				i_result += ft_strlen(exit_code);
				i += 2;
				free(exit_code);
				continue ;
			}
			if (ft_isalpha(arg[i + 1]) || arg[i + 1] == '_')
			{
				char *var = ft_substr(arg, i + 1, get_len_expand_var(arg + i + 1));
				value = ft_strdup("");
				j = 0;
				while (mini->env[j])
				{
					if (ft_strncmp(mini->env[j], var, ft_strlen(var)) == 0
						&& (ft_strlen(var) == get_len_var(mini->env[j])))
					{
						eq = ft_strchr(mini->env[j], '=');
						free(value);
						if (eq)
							value = ft_strdup(eq + 1);
						else
							value = ft_strdup("");
						break ;
					}
					j++;
				}
				ft_memcpy(result + i_result, value, ft_strlen(value));
				i_result += ft_strlen(value);
				i += ft_strlen(var) + 1;
				free(value);
				free(var);
				continue ;
			}
		}
		result[i_result++] = arg[i];
		i++;
	}
	result[i_result] = '\0';
	return (result);
}

void	expand_vars(t_mini *mini, t_token_info *t_info)
{
	int		i;
	char	*temp;
	
	i = 0;
	while (mini->cmd[i])
	{
		if (t_info[i].type_quote != SINGLE_QUOTES)
		{
			temp = mini->cmd[i];
			// Cambio la linea de comandos sustituyendo las variables por su valor
			mini->cmd[i] = expand_vars_in_token(mini, mini->cmd[i]);
			free(temp);
		}
		i++;
	}
}