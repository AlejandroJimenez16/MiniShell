/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 21:42:30 by alejandj          #+#    #+#             */
/*   Updated: 2025/11/24 23:10:54 by alejandj         ###   ########.fr       */
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

	len = get_len_token(mini, arg);
	result = malloc(len * sizeof(char));
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
				printf("%s\n", var);
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