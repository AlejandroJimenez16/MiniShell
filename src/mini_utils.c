/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 19:46:35 by alejandj          #+#    #+#             */
/*   Updated: 2025/10/31 17:37:25 by alejandj         ###   ########.fr       */
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

char	*get_prompt(char **env)
{
	char	*home;
	char	*pwd;
	char	*temp;

	if (!env)
		return (NULL);

	// Obtengo ruta del home
	home = get_home(env);
	// Obtengo la ruta donde estoy
	pwd = getcwd(NULL, 0);
	
	// Si coincide el home con la ruta actual
	if (ft_strncmp(home, pwd, ft_strlen(home)) == 0)
		return ("alejandj@aleconst~$ ");
	// Si hay mas ruta aparte del home
	else if (ft_strncmp(home, pwd, ft_strlen(home)) == 0
		&& (ft_strlen(pwd) > ft_strlen(home)))
	{
		temp = malloc(ft_strlen(pwd) - ft_strlen(home) + 3);
		if (!temp)
			return (NULL);
		temp[0] = '~';
		//temp[1] = '\0';
		ft_strlcat(temp, pwd + ft_strlen(home),
			(ft_strlen(pwd) - ft_strlen(home)) + 3);
		ft_strlcat(temp, "$ ", (ft_strlen(pwd) - ft_strlen(home)) + 3);
		return (temp);
	}
	// No es ta en el home
	else
	{
		temp = malloc(ft_strlen(pwd) + 2);
		if (!temp)
			return (NULL);
		ft_strlcpy(temp, pwd, ft_strlen(pwd) + 2);
		ft_strlcat(temp, " ", ft_strlen(pwd) + 2);
		return (temp);
	}
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
