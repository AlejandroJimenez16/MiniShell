/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 19:46:35 by alejandj          #+#    #+#             */
/*   Updated: 2025/11/05 14:46:53 by alejandj         ###   ########.fr       */
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
	int		full_size;

	if (!env)
		return (NULL);
	home = get_home(env);
	pwd = getcwd(NULL, 0);
	if (ft_strncmp(home, pwd, ft_strlen(home)) == 0 && (ft_strlen(pwd) == ft_strlen(home)))
		return ("alejandj@aleconst:~$ ");
	else if (ft_strncmp(home, pwd, ft_strlen(home)) == 0 && (ft_strlen(pwd) > ft_strlen(home)))
	{
		full_size = ft_strlen("alejandj@aleconst:~") + (ft_strlen(pwd) - ft_strlen(home)) + 3;
		temp = malloc(full_size);
		if (!temp)
			return (NULL);
		ft_strlcpy(temp, "alejandj@aleconst:~", ft_strlen("alejandj@aleconst:~") + 1);
		ft_strlcat(temp, pwd + ft_strlen(home), full_size);
		ft_strlcat(temp, "$ ", full_size);
		return (temp);
	}
	else
	{
		full_size = ft_strlen("alejandj@aleconst:") + ft_strlen(pwd) + 3;
		temp = malloc(full_size);
		if (!temp)
			return (NULL);
		ft_strlcpy(temp, "alejandj@aleconst:", ft_strlen("alejandj@aleconst:") + 1);
		ft_strlcat(temp, pwd, full_size);
		ft_strlcat(temp, "$ ", full_size);
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

void	print_cmd_error(char *cmd, char *error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(error, 2);
}
