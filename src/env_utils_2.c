/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 13:38:34 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/08 21:45:35 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

size_t	get_len_var(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	return (i);
}

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

char	**copy_env(char **env)
{
	int		i;
	int		num_vars;
	char	**new_env;

	num_vars = 0;
	while (env[num_vars] != NULL)
		num_vars++;
	new_env = malloc((num_vars + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

static void	compare_swap_vars(char **s1, char **s2, int *sorted)
{
	char	*var1;
	char	*var2;
	char	*temp;

	var1 = ft_substr(*s1, 0, ft_strchr(*s1, '=') - *s1);
	var2 = ft_substr(*s2, 0, ft_strchr(*s2, '=') - *s2);
	if (ft_strncmp(var1, var2, 1024) > 0)
	{
		temp = *s1;
		*s1 = *s2;
		*s2 = temp;
		*sorted = 0;
	}
	free(var1);
	free(var2);
}

void	sort_env(char **cpy_env)
{
	int		i;
	int		sorted;
	int		len;

	len = 0;
	while (cpy_env[len])
		len++;
	sorted = 0;
	while (sorted == 0)
	{
		sorted = 1;
		i = 0;
		while (i < len - 1)
		{
			compare_swap_vars(&cpy_env[i], &cpy_env[i + 1], &sorted);
			i++;
		}
	}
}
