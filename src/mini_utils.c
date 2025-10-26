/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 19:46:35 by alejandj          #+#    #+#             */
/*   Updated: 2025/10/24 20:56:01 by alejandj         ###   ########.fr       */
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
	char	*prompt;

	if (!env)
		return (NULL);
	home = get_home(env);
	pwd = getcwd(NULL, 0);
	if (!ft_strncmp(home, pwd, ft_strlen(home)))
		return ("alejandj@aleconst~$ ");
	temp = ft_strjoin()
}