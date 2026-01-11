/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 19:46:35 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/04 20:59:53 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static char	*prompt_inside_home(char *home, char *pwd)
{
	int		full_size;
	char	*temp;

	full_size = ft_strlen("alejandj@aleconst:~")
		+ (ft_strlen(pwd) - ft_strlen(home)) + 3;
	temp = malloc(full_size);
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, "alejandj@aleconst:~",
		ft_strlen("alejandj@aleconst:~") + 1);
	ft_strlcat(temp, pwd + ft_strlen(home), full_size);
	ft_strlcat(temp, "$ ", full_size);
	return (temp);
}

static	char	*prompt_outside_home(char *pwd)
{
	int		full_size;
	char	*temp;

	full_size = ft_strlen("alejandj@aleconst:") + ft_strlen(pwd) + 3;
	temp = malloc(full_size);
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, "alejandj@aleconst:", ft_strlen("alejandj@aleconst:") + 1);
	ft_strlcat(temp, pwd, full_size);
	ft_strlcat(temp, "$ ", full_size);
	return (temp);
}

static	char	*prompt_without_env(char *pwd)
{
	int		full_size;
	char	*temp;

	full_size = ft_strlen("alejandj@aleconst:~") + ft_strlen(pwd) + 3;
	temp = malloc(full_size);
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, "alejandj@aleconst:~",
		ft_strlen("alejandj@aleconst:~") + 1);
	ft_strlcat(temp, pwd, full_size);
	ft_strlcat(temp, "$ ", full_size);
	return (temp);
}

char	*get_prompt(int has_env, char **env)
{
	char	*prompt;
	char	*home;
	char	*pwd;

	if (!has_env)
	{
		pwd = getcwd(NULL, 0);
		prompt = prompt_without_env(pwd);
		free(pwd);
		return (prompt);
	}
	home = get_env("HOME", env);
	pwd = getcwd(NULL, 0);
	if (ft_strncmp(home, pwd, ft_strlen(home)) == 0
		&& (ft_strlen(pwd) == ft_strlen(home)))
		prompt = ft_strdup("alejandj@aleconst:~$ ");
	else if (ft_strncmp(home, pwd, ft_strlen(home)) == 0
		&& (ft_strlen(pwd) > ft_strlen(home)))
		prompt = prompt_inside_home(home, pwd);
	else
		prompt = prompt_outside_home(pwd);
	free(pwd);
	return (prompt);
}
