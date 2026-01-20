/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:34:56 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/20 20:43:59 by alejandj         ###   ########.fr       */
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
		if (oldpwd)
			free(oldpwd);
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

	if (cmd[1] && cmd[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (mini->exit_code = 1, 1);
	}
	path = cmd[1];
	if (path == NULL)
	{
		path = get_env("HOME", mini->env);
		if (!path)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			return (mini->exit_code = 1, 1);
		}
	}
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (mini->exit_code = 1, 1);
	}
	return (update_pwd(mini));
}
