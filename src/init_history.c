/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 12:50:27 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/30 15:42:05 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	read_add(t_mini *mini)
{
	char	*line;

	line = get_next_line(mini->history_fd);
	while (line)
	{
		if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		add_history(line);
		free(line);
		line = get_next_line(mini->history_fd);
	}
}

void	ft_init_history(t_mini *mini)
{
	char	*home;
	char	*env_home;

	env_home = get_env("HOME", mini->env);
	if (!env_home)
		return ;
	home = ft_strdup(env_home);
	if (!home)
		return ;
	create_path(&home, FILENAME);
	mini->history_fd = open(home, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (mini->history_fd < 0)
	{
		free(home);
		return ;
	}
	free(home);
	read_add(mini);
}

void	ft_add_to_history(t_mini *mini)
{
	add_history(mini->line);
	if (mini->history_fd != -1)
	{
		ft_putstr_fd(mini->line, mini->history_fd);
		ft_putchar_fd('\n', mini->history_fd);
	}
}
