/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 12:50:27 by alejandj          #+#    #+#             */
/*   Updated: 2026/01/22 15:57:28 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	ft_init_history(t_mini *mini)
{
	char	*home;
	char	*line;

	home = ft_strdup(get_env("HOME", mini->env));
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
