/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:34:56 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/03 21:22:48 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static int	update_pwd(t_mini *mini)
{
	char	*pwd;
	char	*oldpwd;
	char	*temp;

	temp = get_env("PWD", mini->env);
	if (temp)
		oldpwd = ft_strdup(temp);
	else
		oldpwd = NULL;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("minishell: getcwd");
		mini->exit_code = 1;
		return (1);
	}
	if (oldpwd)
		set_env(mini, "OLDPWD", oldpwd);
	set_env(mini, "PWD", pwd);
	free(oldpwd);
	free(pwd);
	return (0);
}

int	ft_cd(char **cmd, t_mini *mini)
{
	char	*path;

	path = cmd[1];
	if (path == NULL)
	{
		path = get_env("HOME", mini->env);
		if (!path)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			mini->exit_code = 1;
			return (1);
		}
	}
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": No such file or directory", 2);
		mini->exit_code = 1;
		return (1);
	}
	return (update_pwd(mini));
}
