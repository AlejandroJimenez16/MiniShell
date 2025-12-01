/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 13:00:08 by alejandj          #+#    #+#             */
/*   Updated: 2025/12/01 13:00:56 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

char	*get_home(char **env)
{
	int		i;
	char	*pwd;
	int		len;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i] != NULL)
	{
		if (!ft_strncmp(env[i], "HOME=", 5))
		{
			len = ft_strlen(env[i] + 5);
			pwd = malloc((len + 1) * sizeof(char));
			ft_strlcpy(pwd, env[i] + 5, len + 1);
		}
		i++;
	}
	return (pwd);
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
